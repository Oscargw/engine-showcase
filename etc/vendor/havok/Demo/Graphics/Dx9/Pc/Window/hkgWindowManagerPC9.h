/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#ifndef HK_GRAPHICS_WINDOW_MANAGER_PC9_H
#define HK_GRAPHICS_WINDOW_MANAGER_PC9_H

#include <Graphics/Dx9/Pc/Window/hkgWindowDX9PC.h>

//
// It is not Havok mem managed as we
// may need to have the manager present after 
// hkBaseSystem:: quit just to tell the wndproc 
// that the havok managed window system has shut down (hkgWindow list is empty)
// It should not be a big mem resource anyway and is only on PC.
// Add, find, and remove use a critical section for the map access
//

class hkgWindowManagerDX9PC: public hkReferencedObject, public hkSingleton<hkgWindowManagerDX9PC>
{
public:
	
	// There should be no need to create more than one of these,
	// and that one is created globally.

	hkgWindowManagerDX9PC();
	~hkgWindowManagerDX9PC();

	// will not reference actual hkgWindow as it 
	// will assume that windows are only added and 
	// removed under hkgWindow dtor and ctor
	bool addWindow( HWND handle, hkgWindowDX9PC* w );
	bool setHWND( HWND handle, hkgWindowDX9PC* w );

	hkgWindowDX9PC* findWindow( HWND handle ) const;
	
	bool removeWindow( HWND handle );
	
protected:
	
	struct WindowMap
	{
		void* handle;
		hkgWindowDX9PC* window;
	};

	hkArray<WindowMap> m_hwndMap; 
	HANDLE m_hMutex;
};

#endif // HK_GRAPHICS_WINDOW_MANAGER_PC9_H

/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20080925)
* 
* Confidential Information of Havok.  (C) Copyright 1999-2008
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
* 
* Use of this software for evaluation purposes is subject to and indicates
* acceptance of the End User licence Agreement for this product. A copy of
* the license is included with this software and is also available at www.havok.com/tryhavok.
* 
*/