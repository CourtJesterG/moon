/* 
 * deployment.cpp: Deployment Class support
 *
 * Copyright 2008 Novell, Inc.  (http://www.novell.com)
 *
 * See the LICENSE file included with the distribution for details.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>

#include "deployment.h"
#include <stdlib.h>
#include <mono/jit/jit.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
G_BEGIN_DECLS
/* because this header sucks */
#include <mono/metadata/mono-debug.h>
G_END_DECLS
#include <mono/metadata/mono-config.h>


gboolean Deployment::initialized = FALSE;
pthread_key_t Deployment::tls_key = 0;
pthread_mutex_t Deployment::hash_mutex;
GHashTable* Deployment::current_hash = NULL;
MonoDomain* Deployment::root_domain = NULL;

 
bool
Deployment::Initialize()
{
	char *trace_options;

	if (initialized)
		return true;
#if DEBUG
	g_warning ("Enabling MONO_DEBUG=keep-delegates.");
	g_setenv ("MONO_DEBUG", "keep-delegates", false);
#endif

	mono_config_parse (NULL);
	trace_options = getenv ("MOON_TRACE");
	if (trace_options != NULL){
		printf ("Setting trace options to: %s\n", trace_options);
		mono_jit_set_trace_options (trace_options);
	}
       
	mono_debug_init (MONO_DEBUG_FORMAT_MONO);
	root_domain = mono_jit_init_version ("Moonlight Root Domain", "moonlight");

	initialized = true;
	current_hash = g_hash_table_new (g_direct_hash, g_direct_equal);
	pthread_key_create (&tls_key, NULL);
	pthread_mutex_init (&hash_mutex, NULL);

	return true;
}


Deployment*
Deployment::GetCurrent()
{
	Deployment *deployment = (Deployment *) pthread_getspecific (tls_key);
	MonoDomain *current_domain = mono_domain_get ();

	/*
	 * If we dont have a Deployment* in the TLS slot then we are in a thread created
	 * by mono.  In this case we look up in the hsah table the deployment against 
	 * the current appdomain
	 */ 
	if (deployment == NULL) {
		pthread_mutex_lock (&hash_mutex);
		deployment = (Deployment *) g_hash_table_lookup (current_hash, current_domain);
		pthread_mutex_unlock (&hash_mutex);
	}

	/*
	 * If we have a domain mismatch, fix that before we continue
	 */
	if (deployment && deployment->domain != current_domain)
		mono_domain_set (deployment->domain, FALSE);

	return deployment;
}

void
Deployment::SetCurrent (Deployment* deployment)
{
	mono_domain_set (deployment->domain, FALSE);
	pthread_setspecific (tls_key, deployment);
}

Deployment::Deployment()
{
        char *domain_name = g_strdup_printf ("moonlight-%p", this);

	SetObjectType (Type::DEPLOYMENT);
	types = new Types ();
	current_app = NULL;
	mono_domain_set (root_domain, FALSE);
        domain = mono_domain_create_appdomain (domain_name, NULL);
        g_free (domain_name);

        mono_domain_set (domain, FALSE);

	pthread_mutex_lock (&hash_mutex);
	g_hash_table_insert (current_hash, domain, this);
	pthread_mutex_unlock (&hash_mutex);
}

Deployment::~Deployment()
{
	pthread_mutex_lock (&hash_mutex);
	g_hash_table_remove (current_hash, domain);
	pthread_mutex_unlock (&hash_mutex);

	mono_domain_set (root_domain, FALSE);
	mono_domain_unload (domain);

	delete types;
}

Types*
Deployment::GetTypes ()
{
	return types;
}

Application*
Deployment::GetCurrentApplication ()
{
	return current_app;
}

void
Deployment::SetCurrentApplication (Application* value)
{
	if (current_app == value)
		return;

	if (current_app)
		current_app->unref ();

	current_app = value;

	if (current_app)
	  current_app->ref ();
}

AssemblyPart::AssemblyPart ()
{
	SetObjectType (Type::ASSEMBLYPART);
}

AssemblyPart::~AssemblyPart ()
{
}

AssemblyPartCollection::AssemblyPartCollection ()
{
	SetObjectType (Type::ASSEMBLYPART_COLLECTION);
}

AssemblyPartCollection::~AssemblyPartCollection ()
{
}
