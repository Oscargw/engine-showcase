#
# Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
# prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
# Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
#

## python

"""
Module hkb -- custom attribute definitions for Behavior

All global identifiers in this file are available as custom attributes.
"""

import hk

class RoleAttribute(hk.Attribute):
    def __call__(self, role, flags="FLAG_NONE"):
        return self.struct_initialzer("hkbRoleAttribute::%s,%s"%(role, "|".join("hkbRoleAttribute::"+f for f in flags.split("|")) ) )

#
# Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20080925)
# 
# Confidential Information of Havok.  (C) Copyright 1999-2008
# Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
# Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
# rights, and intellectual property rights in the Havok software remain in
# Havok and/or its suppliers.
# 
# Use of this software for evaluation purposes is subject to and indicates
# acceptance of the End User licence Agreement for this product. A copy of
# the license is included with this software and is also available at www.havok.com/tryhavok.
# 
#
