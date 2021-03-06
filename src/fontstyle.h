/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * fontstyle.h: 
 *
 * Contact:
 *   Moonlight List (moonlight-list@lists.ximian.com)
 *
 * Copyright 2009 Novell, Inc. (http://www.novell.com)
 *
 * See the LICENSE file included with the distribution for details.
 */

#ifndef __FONT_STYLE_H__
#define __FONT_STYLE_H__

namespace Moonlight {

/* @IncludeInKinds */
struct FontStyle {
	FontStyles style;

	FontStyle (FontStyles style)
	{
		this->style = style;
	}

	bool operator== (const FontStyle &v) const
	{
		return v.style == style;
	}
	
	bool operator!= (const FontStyle &v) const
	{
		return !(*this == v);
	}
};

};
#endif /* __FONT_STYLE_H__ */
