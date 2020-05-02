/*
 * mode -	a game mode is a single session of operating the engine under a relatively
 *			uniform set of rules. as in any section of this engine, custom code can be
 * 			inserted at any stage of the mode pipeline, but the mode structure ensures
 * 			a particular degree of...well...structure. currently mode only exists as a
 * 			structure, but auxiliary functionality may be implemented as it represents
 * 			the ideal implementation framework of the underlying objects as well. this
 * 			allows for the implementation of strikingly similar functionality on every
 * 			layer of the game's processing cycles
 */
#ifndef __MODE_H__
#define __MODE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
typedef struct mode {
	bool (*init)(void);
	bool (*render)(void);
	bool (*input)(void);
	bool (*routine)(void);
	bool (*free)(void);
} mode;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MODE_H__ */
