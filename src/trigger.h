/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * trigger.h
 *
 * Copyright 2007 Novell, Inc. (http://www.novell.com)
 *
 * See the LICENSE file included with the distribution for details.
 * 
 */

#ifndef __MOON_TRIGGER_H__
#define __MOON_TRIGGER_H__

#include <glib.h>

#include "dependencyobject.h"

/* @Namespace=None */
class TriggerAction : public DependencyObject {
public:
	/* @GenerateCBinding,GeneratePInvoke */
	TriggerAction () {}
	
	virtual Type::Kind GetObjectType () { return Type::TRIGGERACTION; }
	
	/* @GenerateCBinding */
	virtual void Fire () {}

protected:
	virtual ~TriggerAction () {}
};


/* @ContentProperty="Actions" */
/* @Namespace=System.Windows */
class EventTrigger : public DependencyObject {
public:
	/* @PropertyType=TriggerActionCollection,ManagedFieldAccess=Internal,ManagedSetterAccess=Internal */
	static DependencyProperty *ActionsProperty;
	/* @PropertyType=string,ManagedPropertyType=RoutedEvent,ManagedFieldAccess=Internal */
	static DependencyProperty *RoutedEventProperty;
	
	/* @GenerateCBinding,GeneratePInvoke */
	EventTrigger ();
	
	virtual Type::Kind GetObjectType () { return Type::EVENTTRIGGER; }

	void SetTarget (DependencyObject *target);
	void RemoveTarget (DependencyObject *target);

protected:
	virtual ~EventTrigger ();

private:
	int registered_event_id;
	static void event_trigger_fire_actions (EventObject *sender, EventArgs *calldata, gpointer closure);
};

G_BEGIN_DECLS
void event_trigger_action_add (EventTrigger *trigger, TriggerAction *action);
G_END_DECLS

#endif /* __MOON_TRIGGER_H__ */
