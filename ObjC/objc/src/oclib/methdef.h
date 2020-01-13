
/*
 * Copyright (c) 1998 David Stes.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id: methdef.h,v 1.1.1.1 2000/06/07 21:09:25 stes Exp $
 */

@interface MethodDef : Def
{
  id unit;
  BOOL factory;
  id method;
  id body;
  char *impname;
  char *selname;
  id classdef;
  id breakpt;
}

- (unsigned)hash;
- (BOOL)isEqual:x;

- (BOOL)factory;
- (BOOL)ismethdef;
- factory:(BOOL)flag;
- method:aDecl;
- body:aBody;
- classdef:aClass;
- (char*)impname;
- (char*)selname;
- method;
- selector;

- prototype;
- synth;
- gen;

- setbreak:bkpt;
- fcall:x;

@end
 
