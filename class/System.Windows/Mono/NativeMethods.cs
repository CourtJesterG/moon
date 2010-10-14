//
// NativeMethods.cs
//
// Contact:
//   Moonlight List (moonlight-list@lists.ximian.com)
//
// Copyright 2007 Novell, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

using System;
using System.Globalization;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Security;
using System.Windows;
using System.Windows.Markup;
using System.Windows.Messaging;

namespace Mono {
	internal enum HttpRequestOptions {
		OptionsNone = 0,
		CustomHeaders = 1,
		DisableCache = 2,
		DisableFileStorage = 4, /* Data will not be written to disk. User must listen to the Write event */
		DisableAsyncSend = 8,
	}
	
	internal enum DownloaderAccessPolicy {
		DownloaderPolicy,
		MediaPolicy,
		XamlPolicy,
		FontPolicy,
		StreamingPolicy,
		MsiPolicy,
		NoPolicy
	}

	internal enum MoonWindowType {
		FullScreen,
		Desktop,
		Plugin
	};

	internal delegate void MentorChangedCallback (IntPtr doptr, IntPtr mentor_ptr);
	internal delegate void EnsureManagedPeerCallback (IntPtr doptr);
	internal delegate void AttachCallback (IntPtr doptr);
	internal delegate void StrongRefCallback (IntPtr referer, IntPtr referent, string name);
	internal delegate Size MeasureOverrideCallback (Size availableSize, ref MoonError error);
	internal delegate Size ArrangeOverrideCallback (Size finalSize, ref MoonError error);
	internal delegate void LoadedCallback (IntPtr fwe_ptr);

	internal delegate void GetDefaultStyleCallback (IntPtr fwe_ptr, out IntPtr styles_array);
	internal delegate IntPtr GetDefaultTemplateCallback (IntPtr fwe_ptr);
	internal delegate void ConvertSetterValuesCallback (IntPtr style_ptr);
	internal delegate void ConvertKeyframeValueCallback (Mono.Kind kind, IntPtr property, IntPtr original, out Value converted);
	internal delegate ManagedStreamCallbacks GetResourceCallback (IntPtr resourceBase, IntPtr name);

	// Used in databinding to interact with managed objects
	internal delegate Value GetValueCallback ();
	internal delegate void SetValueCallback (IntPtr value);

	internal delegate IntPtr CreateCustomXamlElementCallback (string xmlns, string name);
	internal delegate void SetCustomXamlAttributeCallback (IntPtr target, string name, string value);
	internal delegate void XamlHookupEventCallback (IntPtr target, string name, string value);
	internal delegate void UnmanagedEventHandler (IntPtr sender, IntPtr calldata, IntPtr closure);

	internal delegate void PlainEvent (IntPtr target);
	internal delegate void GDestroyNotify (IntPtr target);

	internal delegate void AsyncResponseAvailableHandler (IntPtr response, IntPtr context);
	internal delegate void UnmanagedPropertyChangeHandler (IntPtr dependency_object, IntPtr propertyChangedArgs, ref MoonError error, IntPtr closure);

	internal delegate void TickCallHandler (IntPtr handle);


	internal delegate bool InvalidateHandleDelegate (IntPtr obj_handle);

	internal delegate bool HasMemberDelegate (IntPtr obj_handle,
						  [MarshalAs (UnmanagedType.LPStr)] string name);

	internal delegate bool InvokeDelegate (IntPtr obj_handle,
					       [MarshalAs (UnmanagedType.LPStr)] string name,
					       [MarshalAs (UnmanagedType.LPArray, SizeParamIndex = 3)]
					       IntPtr[] args,
					       int arg_count,
					       ref Value return_value,
					       out string exc_string);

	internal delegate bool SetPropertyDelegate (IntPtr obj_handle,
						    [MarshalAs (UnmanagedType.LPStr)] string name,
						    [MarshalAs (UnmanagedType.LPArray, SizeParamIndex = 3)]
						    IntPtr[] args,
						    int arg_count,
						    ref Value return_value,
						    out string exc_string);

	internal delegate bool GetPropertyDelegate (IntPtr obj_handle,
						    [MarshalAs (UnmanagedType.LPStr)] string name,
						    [MarshalAs (UnmanagedType.LPArray, SizeParamIndex = 3)]
						    IntPtr[] args,
						    int arg_count,
						    ref Value return_value,
						    out string exc_string);
	
	internal delegate void HttpHeaderVisitor (IntPtr context, IntPtr name, IntPtr val);

	internal delegate void DomEventCallback (IntPtr context, string name, int client_x, int client_y, int offset_x, int offset_y, 
		[MarshalAs (UnmanagedType.Bool)] bool alt_key,	// glib gboolean is a gint (i.e. 4 bytes just like the FX bool)
		[MarshalAs (UnmanagedType.Bool)] bool ctrl_key,
		[MarshalAs (UnmanagedType.Bool)] bool shift_key, 
		int /* System.Windows.Browser.MouseButtons */ mouse_button,
		int key_code,
		int char_code,
		IntPtr domEvent);

	internal delegate bool ImageUriFunc (int level, int posx, int posy, ref IntPtr uri, IntPtr ignore);

	internal delegate IntPtr System_Uri_Ctor_1 (string uri_string);
	internal delegate IntPtr System_Uri_Ctor_2 (string uri_string, UriKind uri_kind);
	internal delegate IntPtr System_Uri_Ctor_3 (IntPtr base_uri, string relative_uri);
	internal delegate IntPtr System_Uri_Ctor_4 (IntPtr base_uri, IntPtr relative_uri);
	internal delegate IntPtr System_Uri_GetStringProperty (IntPtr instance);
	internal delegate int System_Uri_GetInt32Property (IntPtr instance);
	internal delegate bool System_Uri_GetBooleanProperty (IntPtr instance);
	internal delegate IntPtr System_Uri_ToString (IntPtr instance);
	internal delegate bool System_Uri_Equals (IntPtr a, IntPtr b);
	internal delegate IntPtr System_Uri_Clone (IntPtr instance);
	internal delegate IntPtr System_Uri_CloneWithScheme (IntPtr instance, string scheme);

	internal struct UriFunctions {
		public System_Uri_Ctor_1 ctor_1;
		public System_Uri_Ctor_2 ctor_2;
		public System_Uri_Ctor_3 ctor_3;
		public System_Uri_Ctor_4 ctor_4;
		public System_Uri_GetStringProperty get_scheme;
		public System_Uri_GetStringProperty get_host;
		public System_Uri_GetInt32Property get_port;
		public System_Uri_GetStringProperty get_fragment;
		public System_Uri_GetStringProperty get_path;
		public System_Uri_GetStringProperty get_query;
		public System_Uri_GetStringProperty get_original_string;
		public System_Uri_GetBooleanProperty get_is_absolute;
		public System_Uri_ToString tostring;
		public System_Uri_Equals equals;
		public System_Uri_CloneWithScheme clone_with_scheme;
		public System_Uri_ToString toescapedstring;
	};

	internal static partial class NativeMethods {
		/*
		 * 
		 * Don't add any P/Invokes here.
		 * 
		 * Add annotations (@GeneratePInvoke) to your C/C++ methods to generate the P/Invokes.
		 * If the generator gets parameters wrong, you can add a @MarshalAs=<whatever> to override.
		 * 
		 */
		internal static Exception CreateManagedException (MoonError err)
		{
			string msg = err.Message;
			Exception ex = null;
			
			if (err.GCHandlePtr != IntPtr.Zero) {
				// We need to get this before calling Dispose.
				ex = err.GCHandle.Target as Exception;
			}

			err.Dispose ();
			
			switch (err.Number) {
			case 1:
			default:
				return new Exception (msg);
			case 2:
				return new ArgumentException (msg);
			case 3:
				return new ArgumentNullException (msg);
			case 4:
				return new ArgumentOutOfRangeException (msg);
			case 5:
				return new InvalidOperationException (msg);
			case 6:
				return new XamlParseException (err.LineNumber, err.CharPosition, msg);
			case 7:
				return new UnauthorizedAccessException (msg);
			case 8:
				return new ExecutionEngineException (msg);
			case 9:
				if (ex != null)
					return ex;
				return new Exception (msg);
			case 10:
				return new ListenFailedException (msg);
			case 11:
				return new SendFailedException (msg);
			case 12:
				return new NotImplementedException (msg);
			case 13:
				return new SecurityException (msg);
			}
		}
	}
}
