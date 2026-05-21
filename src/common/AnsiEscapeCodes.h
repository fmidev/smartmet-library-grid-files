/*! \brief ANSI terminal escape-code macros for coloured and styled text output.
 *
 *  Used by diagnostic print methods when writing to a terminal.  Wrap text with
 *  `ANSI_BOLD_ON … ANSI_BOLD_OFF` or `ANSI_FG_RED … ANSI_RESET` etc. */

#pragma once

/** @name Text attribute codes @{ */
#define ANSI_RESET       "\033[0m"   //!< Reset all attributes
#define ANSI_BOLD_ON     "\033[1m"   //!< Bold / bright on
#define ANSI_ITALIC_ON   "\033[3m"   //!< Italic on
#define ANSI_UNDERLINE_ON "\033[4m"  //!< Underline on
#define ANSI_BLINK_ON    "\033[5m"   //!< Blink on
#define ANSI_INVERSE_ON  "\033[7m"   //!< Inverse video on
#define ANSI_STRIKE_ON   "\033[9m"   //!< Strikethrough on
#define ANSI_BOLD_OFF    "\033[22m"  //!< Bold off
#define ANSI_ITALIC_OFF  "\033[23m"  //!< Italic off
#define ANSI_UNDERLINE_OFF "\033[24m" //!< Underline off
#define ANSI_BLINK_OFF   "\033[25m"  //!< Blink off
#define ANSI_INVERSE_OFF "\033[27m"  //!< Inverse video off
#define ANSI_STRIKE_OFF  "\033[29m"  //!< Strikethrough off
/** @} */
/** @name Foreground colour codes @{ */
#define ANSI_FG_BLACK    "\033[30m"  //!< Black foreground
#define ANSI_FG_RED      "\033[31m"  //!< Red foreground
#define ANSI_FG_GREEN    "\033[32m"  //!< Green foreground
#define ANSI_FG_YELLOW   "\033[33m"  //!< Yellow foreground
#define ANSI_FG_BLUE     "\033[34m"  //!< Blue foreground
#define ANSI_FG_MAGENTA  "\033[35m"  //!< Magenta foreground
#define ANSI_FG_CYAN     "\033[36m"  //!< Cyan foreground
#define ANSI_FG_WHITE    "\033[37m"  //!< White foreground
#define ANSI_FG_DEFAULT  "\033[39m"  //!< Default foreground
/** @} */
/** @name Background colour codes @{ */
#define ANSI_BG_BLACK    "\033[40m"  //!< Black background
#define ANSI_BG_RED      "\033[41m"  //!< Red background
#define ANSI_BG_GREEN    "\033[42m"  //!< Green background
#define ANSI_BG_YELLOW   "\033[43m"  //!< Yellow background
#define ANSI_BG_BLUE     "\033[44m"  //!< Blue background
#define ANSI_BG_MAGENTA  "\033[45m"  //!< Magenta background
#define ANSI_BG_CYAN     "\033[46m"  //!< Cyan background
#define ANSI_BG_WHITE    "\033[47m"  //!< White background
#define ANSI_BG_DEFAULT  "\033[49m"  //!< Default background
/** @} */
