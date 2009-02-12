//
// Unit tests for Inline
//
// Contact:
//   Moonlight List (moonlight-list@lists.ximian.com)
//
// Copyright (C) 2009 Novell, Inc (http://www.novell.com)
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
using System.Windows;
using System.Windows.Documents;
using System.Windows.Media;

using Mono.Moonlight.UnitTesting;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MoonTest.System.Windows.Documents {

	[TestClass]
	public class InlineTest {

		static public void CheckDefaults (Inline i)
		{
			Assert.AreEqual ("Portable User Interface", i.FontFamily.Source, "FontFamily");
			Assert.AreEqual (11, i.FontSize, "FontSize");

			Assert.AreEqual (FontStretches.Normal, i.FontStretch, "FontStretch");
			Assert.AreEqual (FontStyles.Normal, i.FontStyle, "FontStyle");
			Assert.AreEqual (FontWeights.Normal, i.FontWeight, "FontWeight");

			Assert.IsNotNull (i.Foreground, "Foreground");
			Assert.AreEqual (Colors.Black, (i.Foreground as SolidColorBrush).Color);
			
			Assert.AreEqual ("en-us", i.Language.IetfLanguageTag, "Language");
			Assert.IsNull (i.TextDecorations, "TextDecorations");
		}

		static public void CheckTextBlockInherited (Inline i)
		{
			Assert.AreEqual ("Portable User Interface", i.FontFamily.Source, "FontFamily", "1");
			Assert.AreEqual (11, i.FontSize, "FontSize", "2");

			Assert.AreEqual (FontStretches.Normal, i.FontStretch, "FontStretch", "3");
			Assert.AreEqual (FontStyles.Normal, i.FontStyle, "FontStyle", "4");
			Assert.AreEqual (FontWeights.Normal, i.FontWeight, "FontWeight", "5");

			Assert.IsNotNull (i.Foreground, "Foreground", "6");
			Assert.AreEqual (Colors.Black, (i.Foreground as SolidColorBrush).Color, "Foreground.Color", "7");
			Assert.AreEqual ("en-us", i.Language.IetfLanguageTag, "Language", "8");
			Assert.IsNull (i.TextDecorations, "TextDecorations", "9");
		}
	}
}
