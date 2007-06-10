using System;
using System.Runtime.InteropServices;
using Gtk;
using System.Windows;
using System.Windows.Controls;
using Mono;
using System.Reflection;

public class GtkSilver : DrawingArea {
	[DllImport ("moon")]
	extern static IntPtr surface_new (int w, int h);

	[DllImport ("moon")]
	extern static IntPtr surface_get_drawing_area (IntPtr surface);

	[DllImport ("moon")]
	extern static IntPtr surface_attach (IntPtr surface, IntPtr toplevel);

	[DllImport ("moon")]
	extern static IntPtr xaml_create_from_file (string file);
	
	IntPtr surface;
	DrawingArea da;
	
	public GtkSilver (int w, int h)
	{
		surface = surface_new (w, h);
		Raw = surface_get_drawing_area (surface);
	}

	public void Attach (Canvas canvas)
	{
		if (canvas == null)
			throw new ArgumentNullException ("canvas");

		// Dynamically invoke our get-the-handle-code
		MethodInfo m = typeof (Canvas).Assembly.GetType ("Mono.Hosting").
			GetMethod ("GetNativeObject", BindingFlags.Static | BindingFlags.NonPublic);
		IntPtr p = (IntPtr) m.Invoke (null, new object [] { canvas });
		
		surface_attach (surface, p);
	}

	public bool LoadFile (string file)
	{
		if (file == null)
			throw new ArgumentNullException ("file");

		IntPtr x = xaml_create_from_file (file);
		if (x == IntPtr.Zero)
			return false;

		// TODO: Check that x is a Canvas

		MethodInfo m = typeof (Canvas).GetMethod ("FromPtr", BindingFlags.Static | BindingFlags.NonPublic);
		Canvas c = (Canvas) m.Invoke (null, new object [] { x });
		if (c == null)
			return false;
		
		Attach (c);
		
		return true;
	}
}
	
	
