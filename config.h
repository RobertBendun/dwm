/* See LICENSE file for copyright and license details. */

#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int gappx              = 0;        /* initial gap between windows */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "UbuntuMono:size=10", "fontawesome:size=15" };
static const char dmenufont[]       = "UbuntuMono:size=10";

#if 1 // Gruvbox
#define text1 "#fbf1c7"
#define text2 "#d5c4a1"

#define bg1 "#665c54"
#define bg2 "#282828"

#define br1 bg1
#define br2 bg2

#define Color_Selected "#d65d0e"
#endif

#if 0
#define text1 "#ecf0f1" /* selected */
#define text2 "#bdc3c7" /* normal */

#define bg1 "#8e44ed" /* selected */
#define bg2 "#2c3e50" /* normal */

#define br1 bg1 /* selected */
#define br2 "#34495e" /* normal */
#endif

static const char col_gray1[]       = bg2; // background
static const char col_gray2[]       = br2; // inactive window border color
static const char col_gray3[]       = text2; // font color
static const char col_gray4[]       = text1; // current tag and current window font color
static const char col_cyan[]        = br1; // top bar second color and active border

static const char *colors[][3]      = {
	/*                   fg         bg         border   */
	[SchemeNorm]     = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]      = { col_gray4, col_cyan,  "#af3a03"  },
	[SchemeStatus]   = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right
	[SchemeTagsSel]  = { col_gray4, Color_Selected,  "#000000"  }, // Tagbar left selected
  [SchemeTagsNorm] = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected
  [SchemeInfoSel]  = { col_gray4, col_cyan,  "#000000"  }, // infobar middle selected
  [SchemeInfoNorm] = { col_gray3, col_gray1,  "#000000"  }, // infobar middle unselected
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 * WM_CLASS(STRING) = instance, class
	 * WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  iscentered isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         0, 1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0, 0,          0,          -1,        -1 },
	{ "Alacritty",      NULL,     NULL,           0,  0,        0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0, 0,          0,           1,        -1 }, /* xev */
	{ NULL,      NULL,     "Network Manager TUI", 0,  1, 1,          1,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", Color_Selected, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#define STACK_KEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } },

static Key keys[] = {
	/* modifier                     key        function        argument        help */
	STACK_KEYS(MODKEY,                         focus)
	STACK_KEYS(MODKEY|ShiftMask,               push)
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawncwd,       {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawncwd,       {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0}, "Toggle status bar" },
	//{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	//{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0}, "Switch to last tab" },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0}, "Kill current window" },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]}, "Set tiling layout" },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]}, "Set floating layout" },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]}, "Set monocycle layout" },
	{ MODKEY,                       XK_space,  setlayout,      {0}, "Switch to last layout" },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0}, "Make window floating" },
	{ MODKEY,                       XK_s,      togglesticky,   {0}, "Make window sticky" },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0}, "Make window fullscreen" },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 }, "Next monitor" },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 }, "Previous monitor" },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 }, "Move window to next monitor" },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 }, "Move window to previous monitor" },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_g,      setgaps,        {.i = +3}, "Increase gaps between windows" },
	{ MODKEY|ShiftMask,             XK_g,      setgaps,        {.i = -3}, "Decrease gaps between windows" },

	/* MULTIMEDIA KEYS */
#define VOLUME_UPDATE(COMMAND) SHCMD(COMMAND "; kill -44 $(pidof dwmblocks)")
	{ 0, XF86XK_AudioMute,          spawn, VOLUME_UPDATE("pamixer -t"), "Toggle mute" },
	{ 0, XF86XK_AudioRaiseVolume,   spawn, VOLUME_UPDATE("pamixer -i 5 --allow-boost"), "Increase volume" },
	{ 0, XF86XK_AudioLowerVolume,   spawn, VOLUME_UPDATE("pamixer -d 5 --allow-boost"), "Decrease volume" },
#undef VOLUME_UPDATE
	{ 0, XF86XK_AudioMicMute,	      spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle"), "Toggle microphone mute" },

	{ 0, XF86XK_MonBrightnessUp,	  spawn, SHCMD("xbacklight -inc 15"), "Brighter screen" },
	{ 0, XF86XK_MonBrightnessDown,	spawn, SHCMD("xbacklight -dec 15"), "Dimmer screeen" },
	{ 0, XF86XK_Display,            spawn, SHCMD("dmenu-select-monitor-setup"), "Select monitor setup / reset primary monitor" },

	/* PROGRAMS */
	{ 0,      XK_Print,                  spawn, SHCMD("flameshot gui"), "Make a screenshot" },
	{ MODKEY, XK_Print,                  spawn, SHCMD("flameshot full -c"), "Make fullscreen screenshot and copy to clipboard" },
	{ MODKEY, XK_w,                      spawn, SHCMD("firefox"), "Launch Firefox" },
	{	0,      XF86XK_Bluetooth,          spawn, SHCMD("alacritty --title=\"Network Manager TUI\" --command nmtui"), "Launch network settings" },
	{ MODKEY, XK_Escape, spawn, SHCMD("sudo poweroff"), "Turn off computer" },
	// { MODKEY, XK_,                      spawn, SHCMD("qalculate-qt") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
