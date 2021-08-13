#define main dwm_main
#include "dwm.c"
#undef main

static XModifierKeymap *map = NULL;

char const* modifiers[8];

void load_modifiers_names()
{
	int i, j, k = 0;
	int min_keycode, max_keycode, keysyms_per_keycode = 0;

	XDisplayKeycodes(dpy, &min_keycode, &max_keycode);
  XGetKeyboardMapping(dpy, min_keycode, (max_keycode - min_keycode + 1), &keysyms_per_keycode);

	for (i = 0; i < 8; i++) {
		for (j = 0; j < map->max_keypermod; j++) {
				if (map->modifiermap[k]) {
					KeySym ks;
					int index = 0;
					do {
							ks = XKeycodeToKeysym(dpy, map->modifiermap[k], index);
							index++;
					} while ( !ks && index < keysyms_per_keycode);
					if (modifiers[i] == NULL) {
						modifiers[i] = XKeysymToString(ks);
						if (0) {}
						else if (strstr(modifiers[i], "Control")) modifiers[i] = "Control";
						else if (strstr(modifiers[i], "Shift"))   modifiers[i] = "Shift";
						else if (strstr(modifiers[i], "Alt"))     modifiers[i] = "Alt";
						else if (strstr(modifiers[i], "Super"))   modifiers[i] = "Super";
					}
				}
				k++;
		}
	}
}

int main()
{
	if (!(dpy = XOpenDisplay(NULL))
	||  !(map = XGetModifierMapping(dpy))) {
		fprintf(stderr, "unable to open display or load key mappings\n");
		goto fail;
	}

	load_modifiers_names();

	for (int i = 0; i < LENGTH(keys); ++i) {
		if (!keys[i].help && keys[i].func != spawn && keys[i].func != spawncwd)
			continue;

		unsigned int mod = keys[i].mod;
		for (int j = 7; j >= 0; --j) {
			if (mod & (1<<j)) {
				mod &= ~(1<<j);
				printf("%s + ", modifiers[j]);
			}
		}

		printf("%s\t%s", XKeysymToString(keys[i].keysym), keys[i].func == spawncwd ? "(with cwd) " : "");


		if (keys[i].arg.v == dmenucmd) { printf("Launch dmenu prompt\n"); continue; }
		if (keys[i].arg.v == termcmd) { printf("Launch terminal\n"); continue; }

		printf("%s\n", keys[i].help ? keys[i].help : ((char**)keys[i].arg.v)[2]);
	}

	XCloseDisplay(dpy);
	return 0;
fail:
	if (!dpy) XCloseDisplay(dpy);
}
