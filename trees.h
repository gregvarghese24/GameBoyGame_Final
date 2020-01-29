
//{{BLOCK(trees)

//======================================================================
//
//	trees, 512x256@4, 
//	+ palette 256 entries, not compressed
//	+ 159 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 5088 + 4096 = 9696
//
//	Time-stamp: 2018-11-12, 16:00:31
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TREES_H
#define GRIT_TREES_H

#define treesTilesLen 5088
extern const unsigned short treesTiles[2544];

#define treesMapLen 4096
extern const unsigned short treesMap[2048];

#define treesPalLen 512
extern const unsigned short treesPal[256];

#endif // GRIT_TREES_H

//}}BLOCK(trees)
