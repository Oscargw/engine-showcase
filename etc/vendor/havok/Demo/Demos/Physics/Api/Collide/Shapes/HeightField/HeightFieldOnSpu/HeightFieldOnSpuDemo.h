/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// This demo shows how to implement your own heightfield shape.
// To keep things simple, our implementation is a simple hollow
// sphere filled with boxes

#ifndef HeightFieldOnSpuDemo_H
#define HeightFieldOnSpuDemo_H

#include <Demos/DemoCommon/DemoFramework/hkDefaultPhysicsDemo.h>
#include <Common/Base/Thread/Semaphore/hkSemaphoreBusyWait.h>


class HeightFieldOnSpuDemo : public hkDefaultPhysicsDemo
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

		HeightFieldOnSpuDemo(hkDemoEnvironment* env);

		~HeightFieldOnSpuDemo();

		Result stepDemo(); 

		void castRaysOnSpu();

		hkReal m_time;
		
	private:
		HK_ALIGN128( hkSemaphoreBusyWait	m_semaphore );
};

#endif	// SampledHeightFieldDemo_H

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