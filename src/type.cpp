/*
 * Automatically generated from type.cpp.in, do not edit this file directly
 * To regenerate execute typegen.sh
*/

/*
 * type.cpp: Generated code for the type system.
 *
 * Author:
 *   Rolf Bjarne Kvinge (RKvinge@novell.com)
 *
 * Copyright 2007 Novell, Inc. (http://www.novell.com)
 *
 * See the LICENSE file included with the distribution for details.
 * 
 */

#include <config.h>
#include <string.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <malloc.h>
#include <stdlib.h>
#include "runtime.h"
#include "type.h"

/*
	Type implementation
*/

Type** Type::types;
GHashTable* Type::types_by_name = NULL;

Type::Type (char *name, Type::Kind type, Type::Kind parent)
{
	this->name = strdup (name);
	this->type = type;
	this->parent = parent;
}

Type::~Type()
{
	free (name);
}

Type *
Type::RegisterType (char *name, Type::Kind type, bool value_type)
{
	return RegisterType (name, type, Type::INVALID, value_type);
}

void
Type::free_type (gpointer type)
{
	delete (Type*)type;
}

Type *
Type::RegisterType (char *name, Type::Kind type, Type::Kind parent)
{
	return RegisterType (name, type, parent, false);
}

Type *
Type::RegisterType (char *name, Type::Kind type, Type::Kind parent, bool value_type)
{
	if (types == NULL) {
		types = (Type**)calloc (Type::LASTTYPE, sizeof (Type*));
	}
	if (types_by_name == NULL) {
		types_by_name = g_hash_table_new_full (g_str_hash, g_str_equal,
						       NULL, free_type);
	}

	Type *result = new Type (name, type, parent);
	result->value_type = value_type;

	g_assert (types [type] == NULL);

	types [type] = result;
	g_hash_table_insert (types_by_name, result->name, result);

	return result;
}

bool 
Type::IsSubclassOf (Type::Kind super)
{
	if (type == super)
		return true;

	if (parent == super)
		return true;

	if (parent == Type::INVALID)
		return false;

	Type *parent_type = Find (parent);
	
	if (parent_type == NULL)
		return false;
	
	return parent_type->IsSubclassOf (super);
}

Type *
Type::Find (char *name)
{
	Type *result;

	if (types_by_name == NULL)
		return NULL;

	result = (Type*) g_hash_table_lookup (types_by_name, name);

	return result;
}

Type *
Type::Find (Type::Kind type)
{
	return types [type];
}

void
Type::Shutdown ()
{
	if (types) {
		g_free (types);
		types = NULL;
	}
	if (types_by_name) {
		g_hash_table_destroy (types_by_name);
		types_by_name = NULL;
	}
}

bool
type_get_value_type (Type::Kind type)
{
	return Type::Find (type)->value_type;
}

void 
types_init_manually (void)
{
	// Put types that does not inherit from DependencyObject here (manually)

	//Type::RegisterType ("Invalid", Type::INVALID, Value::INVALID);
	Type::RegisterType ("bool", Type::BOOL, true);
	Type::RegisterType ("double", Type::DOUBLE, true);
	Type::RegisterType ("uint64", Type::UINT64, true);
	Type::RegisterType ("int", Type::INT32, true);
	Type::RegisterType ("string", Type::STRING, false);
	Type::RegisterType ("Color", Type::COLOR, true);
	Type::RegisterType ("Point", Type::POINT, true);
	Type::RegisterType ("Rect", Type::RECT, true);
	Type::RegisterType ("RepeatBehaviour", Type::REPEATBEHAVIOR, true);
	Type::RegisterType ("Duration", Type::DURATION, true);
	Type::RegisterType ("int64", Type::INT64, true);
	Type::RegisterType ("TimeSpan", Type::TIMESPAN, true);
	Type::RegisterType ("KeyTime", Type::KEYTIME, true);
	Type::RegisterType ("double*", Type::DOUBLE_ARRAY, false);
	Type::RegisterType ("Point*", Type::POINT_ARRAY, false);
	Type::RegisterType ("Matrix", Type::MATRIX, true);

#if DEBUG
	for (int i = 1; i < Type::LASTTYPE; i++) {
		if (Type::types [i] != NULL)
			continue;

		if (i > 0 && Type::types [i - 1] != NULL)
			printf ("Type %i is not initialized (previous type in enum is '%s')\n", i, Type::types [i - 1]->name);
		else
			printf ("Type %i is not initialized\n", i);
	}
#endif
}

//
// The generated code will be put at the end of the file
//
// We are currently generating:
//	- types_init (), initializes all types that inherit from DependencyObject


void
types_init (void)
{
	Type::RegisterType ("DependencyObject", Type::DEPENDENCY_OBJECT, false);
	Type::RegisterType ("Animation", Type::ANIMATION, Type::TIMELINE);
	Type::RegisterType ("AnimationClock", Type::ANIMATIONCLOCK, Type::CLOCK);
	Type::RegisterType ("ArcSegment", Type::ARCSEGMENT, Type::PATHSEGMENT);
	Type::RegisterType ("BeginStoryboard", Type::BEGINSTORYBOARD, Type::TRIGGERACTION);
	Type::RegisterType ("BezierSegment", Type::BEZIERSEGMENT, Type::PATHSEGMENT);
	Type::RegisterType ("Brush", Type::BRUSH, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("Canvas", Type::CANVAS, Type::PANEL);
	Type::RegisterType ("Clock", Type::CLOCK, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("ClockGroup", Type::CLOCKGROUP, Type::CLOCK);
	Type::RegisterType ("Collection", Type::COLLECTION, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("ColorAnimation", Type::COLORANIMATION, Type::ANIMATION);
	Type::RegisterType ("ColorAnimationUsingKeyFrames", Type::COLORANIMATIONUSINGKEYFRAMES, Type::COLORANIMATION);
	Type::RegisterType ("ColorKeyFrame", Type::COLORKEYFRAME, Type::KEYFRAME);
	Type::RegisterType ("Control", Type::CONTROL, Type::FRAMEWORKELEMENT);
	Type::RegisterType ("DiscreteColorKeyFrame", Type::DISCRETECOLORKEYFRAME, Type::COLORKEYFRAME);
	Type::RegisterType ("DiscreteDoubleKeyFrame", Type::DISCRETEDOUBLEKEYFRAME, Type::DOUBLEKEYFRAME);
	Type::RegisterType ("DiscretePointKeyFrame", Type::DISCRETEPOINTKEYFRAME, Type::POINTKEYFRAME);
	Type::RegisterType ("DoubleAnimation", Type::DOUBLEANIMATION, Type::ANIMATION);
	Type::RegisterType ("DoubleAnimationUsingKeyFrames", Type::DOUBLEANIMATIONUSINGKEYFRAMES, Type::DOUBLEANIMATION);
	Type::RegisterType ("DoubleKeyFrame", Type::DOUBLEKEYFRAME, Type::KEYFRAME);
	Type::RegisterType ("Downloader", Type::DOWNLOADER, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("Ellipse", Type::ELLIPSE, Type::SHAPE);
	Type::RegisterType ("EllipseGeometry", Type::ELLIPSEGEOMETRY, Type::GEOMETRY);
	Type::RegisterType ("EventTrigger", Type::EVENTTRIGGER, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("FrameworkElement", Type::FRAMEWORKELEMENT, Type::UIELEMENT);
	Type::RegisterType ("Geometry", Type::GEOMETRY, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("GeometryCollection", Type::GEOMETRY_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("GeometryGroup", Type::GEOMETRYGROUP, Type::GEOMETRY);
	Type::RegisterType ("Glyphs", Type::GLYPHS, Type::FRAMEWORKELEMENT);
	Type::RegisterType ("GradientBrush", Type::GRADIENTBRUSH, Type::BRUSH);
	Type::RegisterType ("GradientStop", Type::GRADIENTSTOP, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("GradientStopCollection", Type::GRADIENTSTOP_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("Image", Type::IMAGE, Type::MEDIABASE);
	Type::RegisterType ("ImageBrush", Type::IMAGEBRUSH, Type::TILEBRUSH);
	Type::RegisterType ("Inline", Type::INLINE, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("Inlines", Type::INLINES, Type::COLLECTION);
	Type::RegisterType ("KeyFrame", Type::KEYFRAME, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("KeyFrameCollection", Type::KEYFRAME_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("KeySpline", Type::KEYSPLINE, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("Line", Type::LINE, Type::SHAPE);
	Type::RegisterType ("LinearColorKeyFrame", Type::LINEARCOLORKEYFRAME, Type::COLORKEYFRAME);
	Type::RegisterType ("LinearDoubleKeyFrame", Type::LINEARDOUBLEKEYFRAME, Type::DOUBLEKEYFRAME);
	Type::RegisterType ("LinearGradientBrush", Type::LINEARGRADIENTBRUSH, Type::GRADIENTBRUSH);
	Type::RegisterType ("LinearPointKeyFrame", Type::LINEARPOINTKEYFRAME, Type::POINTKEYFRAME);
	Type::RegisterType ("LineBreak", Type::LINEBREAK, Type::INLINE);
	Type::RegisterType ("LineGeometry", Type::LINEGEOMETRY, Type::GEOMETRY);
	Type::RegisterType ("LineSegment", Type::LINESEGMENT, Type::PATHSEGMENT);
	Type::RegisterType ("MatrixTransform", Type::MATRIXTRANSFORM, Type::TRANSFORM);
	Type::RegisterType ("MediaAttribute", Type::MEDIAATTRIBUTE, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("MediaAttributeCollection", Type::MEDIAATTRIBUTE_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("MediaBase", Type::MEDIABASE, Type::FRAMEWORKELEMENT);
	Type::RegisterType ("MediaElement", Type::MEDIAELEMENT, Type::MEDIABASE);
	Type::RegisterType ("NameScope", Type::NAMESCOPE, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("Panel", Type::PANEL, Type::FRAMEWORKELEMENT);
	Type::RegisterType ("ParallelTimeline", Type::PARALLELTIMELINE, Type::TIMELINEGROUP);
	Type::RegisterType ("Path", Type::PATH, Type::SHAPE);
	Type::RegisterType ("PathFigure", Type::PATHFIGURE, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("PathFigureCollection", Type::PATHFIGURE_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("PathGeometry", Type::PATHGEOMETRY, Type::GEOMETRY);
	Type::RegisterType ("PathSegment", Type::PATHSEGMENT, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("PathSegmentCollection", Type::PATHSEGMENT_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("PointAnimation", Type::POINTANIMATION, Type::ANIMATION);
	Type::RegisterType ("PointAnimationUsingKeyFrames", Type::POINTANIMATIONUSINGKEYFRAMES, Type::POINTANIMATION);
	Type::RegisterType ("PointKeyFrame", Type::POINTKEYFRAME, Type::KEYFRAME);
	Type::RegisterType ("PolyBezierSegment", Type::POLYBEZIERSEGMENT, Type::PATHSEGMENT);
	Type::RegisterType ("Polygon", Type::POLYGON, Type::SHAPE);
	Type::RegisterType ("Polyline", Type::POLYLINE, Type::SHAPE);
	Type::RegisterType ("PolyLineSegment", Type::POLYLINESEGMENT, Type::PATHSEGMENT);
	Type::RegisterType ("PolyQuadraticBezierSegment", Type::POLYQUADRATICBEZIERSEGMENT, Type::PATHSEGMENT);
	Type::RegisterType ("QuadraticBezierSegment", Type::QUADRATICBEZIERSEGMENT, Type::PATHSEGMENT);
	Type::RegisterType ("RadialGradientBrush", Type::RADIALGRADIENTBRUSH, Type::GRADIENTBRUSH);
	Type::RegisterType ("Rectangle", Type::RECTANGLE, Type::SHAPE);
	Type::RegisterType ("RectangleGeometry", Type::RECTANGLEGEOMETRY, Type::GEOMETRY);
	Type::RegisterType ("ResourceCollection", Type::RESOURCE_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("RotateTransform", Type::ROTATETRANSFORM, Type::TRANSFORM);
	Type::RegisterType ("Run", Type::RUN, Type::INLINE);
	Type::RegisterType ("ScaleTransform", Type::SCALETRANSFORM, Type::TRANSFORM);
	Type::RegisterType ("Shape", Type::SHAPE, Type::FRAMEWORKELEMENT);
	Type::RegisterType ("SkewTransform", Type::SKEWTRANSFORM, Type::TRANSFORM);
	Type::RegisterType ("SolidColorBrush", Type::SOLIDCOLORBRUSH, Type::BRUSH);
	Type::RegisterType ("SplineColorKeyFrame", Type::SPLINECOLORKEYFRAME, Type::COLORKEYFRAME);
	Type::RegisterType ("SplineDoubleKeyFrame", Type::SPLINEDOUBLEKEYFRAME, Type::DOUBLEKEYFRAME);
	Type::RegisterType ("SplinePointKeyFrame", Type::SPLINEPOINTKEYFRAME, Type::POINTKEYFRAME);
	Type::RegisterType ("Storyboard", Type::STORYBOARD, Type::PARALLELTIMELINE);
	Type::RegisterType ("StrokeCollection", Type::STROKE_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("StylusPointCollection", Type::STYLUSPOINT_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("TextBlock", Type::TEXTBLOCK, Type::FRAMEWORKELEMENT);
	Type::RegisterType ("TileBrush", Type::TILEBRUSH, Type::BRUSH);
	Type::RegisterType ("Timeline", Type::TIMELINE, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("TimelineCollection", Type::TIMELINE_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("TimelineGroup", Type::TIMELINEGROUP, Type::TIMELINE);
	Type::RegisterType ("TimelineMarker", Type::TIMELINEMARKER, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("TimelineMarkerCollection", Type::TIMELINEMARKER_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("Transform", Type::TRANSFORM, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("TransformCollection", Type::TRANSFORM_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("TransformGroup", Type::TRANSFORMGROUP, Type::TRANSFORM);
	Type::RegisterType ("TranslateTransform", Type::TRANSLATETRANSFORM, Type::TRANSFORM);
	Type::RegisterType ("TriggerAction", Type::TRIGGERACTION, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("TriggerActionCollection", Type::TRIGGERACTION_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("TriggerCollection", Type::TRIGGER_COLLECTION, Type::COLLECTION);
	Type::RegisterType ("UIElement", Type::UIELEMENT, Type::VISUAL);
	Type::RegisterType ("VideoBrush", Type::VIDEOBRUSH, Type::TILEBRUSH);
	Type::RegisterType ("Visual", Type::VISUAL, Type::DEPENDENCY_OBJECT);
	Type::RegisterType ("VisualCollection", Type::VISUAL_COLLECTION, Type::COLLECTION);
	types_init_manually ();
}
