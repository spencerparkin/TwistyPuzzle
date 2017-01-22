// Cuboid3x3x5.h

#pragma once

// To implement this, we need 6*2 cut-planes where only
// 1 or 2 of the extra 6 cut-planes could ever be used,
// provided there are 9 cubies to be captured.  We would
// have to keep track of the shape-shifting cubies to
// know when we can rotate them.  We might as well generalize
// here so that we can support the X-cube along with any
// variant that is a 3x3x3 core with one or more 3x3x1
// layers added on a side.

// Cuboid3x3x5.h