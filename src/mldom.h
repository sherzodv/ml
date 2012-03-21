#ifndef mldom_h
#define mldom_h

#include <stdint.h>
#include <stdio.h>
#include <mlstack.h>

enum ml_error
{
	MLERR_ENCODING = -2
	, MLERR_EOF = -1
	, ML_OK = 0
	, MLERR_NO_TRANSITION
};

enum ml_word
{
	MLWORD_UNKNOWN

	// HTML 4 words
	
	, MLWORD_DOCTYPE, MLWORD_PUBLIC

	, MLWORD_a, MLWORD_b, MLWORD_i
	, MLWORD_p, MLWORD_q, MLWORD_s
	, MLWORD_u

	, MLWORD_id, MLWORD_br, MLWORD_dd
	, MLWORD_dl, MLWORD_dt, MLWORD_em
	, MLWORD_h1, MLWORD_h2, MLWORD_h3
	, MLWORD_h4, MLWORD_h5, MLWORD_h6
	, MLWORD_hr, MLWORD_li, MLWORD_ol
	, MLWORD_td, MLWORD_th, MLWORD_tr
	, MLWORD_tt, MLWORD_ul

	, MLWORD_bdo, MLWORD_big, MLWORD_col
	, MLWORD_del, MLWORD_dfn, MLWORD_dir
	, MLWORD_div, MLWORD_img, MLWORD_ins
	, MLWORD_kbd, MLWORD_map, MLWORD_pre
	, MLWORD_sub, MLWORD_sup, MLWORD_var
	, MLWORD_alt, MLWORD_for, MLWORD_rel
	, MLWORD_rev, MLWORD_src

	, MLWORD_abbr, MLWORD_area, MLWORD_base
	, MLWORD_body, MLWORD_cite, MLWORD_code
	, MLWORD_font, MLWORD_form, MLWORD_head
	, MLWORD_html, MLWORD_link, MLWORD_menu
	, MLWORD_meta, MLWORD_samp, MLWORD_span
	, MLWORD_axis, MLWORD_char, MLWORD_cols
	, MLWORD_data, MLWORD_face, MLWORD_href
	, MLWORD_lang, MLWORD_name, MLWORD_rows
	, MLWORD_size, MLWORD_text, MLWORD_type

	, MLWORD_frame, MLWORD_input, MLWORD_label
	, MLWORD_param, MLWORD_small, MLWORD_style
	, MLWORD_table, MLWORD_tbody, MLWORD_tfoot
	, MLWORD_thead, MLWORD_title, MLWORD_alink
	, MLWORD_class, MLWORD_clear, MLWORD_color
	, MLWORD_defer, MLWORD_ismap, MLWORD_media
	, MLWORD_rules, MLWORD_scope, MLWORD_shape
	, MLWORD_start, MLWORD_value, MLWORD_vlink
	, MLWORD_width, MLWORD_align

	, MLWORD_applet, MLWORD_button, MLWORD_center
	, MLWORD_iframe, MLWORD_legend, MLWORD_object
	, MLWORD_option, MLWORD_script, MLWORD_select
	, MLWORD_strike, MLWORD_strong, MLWORD_accept
	, MLWORD_action, MLWORD_border, MLWORD_coords
	, MLWORD_height, MLWORD_hspace, MLWORD_method
	, MLWORD_nohref, MLWORD_nowrap, MLWORD_onblur
	, MLWORD_onload, MLWORD_prompt, MLWORD_target
	, MLWORD_usemap, MLWORD_valign, MLWORD_vspace

	, MLWORD_acronym, MLWORD_caption, MLWORD_isindex
	, MLWORD_archive, MLWORD_bgcolor, MLWORD_classid
	, MLWORD_charoff, MLWORD_charset, MLWORD_checked
	, MLWORD_colspan, MLWORD_compact, MLWORD_content
	, MLWORD_declare, MLWORD_enctype, MLWORD_headers
	, MLWORD_noshade, MLWORD_onclick, MLWORD_onkeyup
	, MLWORD_onfocus, MLWORD_onreset, MLWORD_profile
	, MLWORD_rowspan, MLWORD_standby, MLWORD_summary
	, MLWORD_version, MLWORD_onerror

	, MLWORD_textarea, MLWORD_basefont, MLWORD_colgroup
	, MLWORD_fieldset, MLWORD_frameset, MLWORD_noframes
	, MLWORD_noscript, MLWORD_optgroup, MLWORD_codebase
	, MLWORD_codetype, MLWORD_datetime, MLWORD_disabled
	, MLWORD_hreflang, MLWORD_language, MLWORD_longdesc
	, MLWORD_multiple, MLWORD_noresize, MLWORD_onchange
	, MLWORD_onselect, MLWORD_onsubmit, MLWORD_onunload
	, MLWORD_readonly, MLWORD_selected, MLWORD_tabindex

	, MLWORD_accesskey, MLWORD_maxlength, MLWORD_onkeydown
	, MLWORD_onmouseup, MLWORD_scrolling, MLWORD_valuetype

	, MLWORD_blockquote, MLWORD_background, MLWORD_http_equiv
	, MLWORD_ondblclick, MLWORD_onkeypress, MLWORD_onmouseout

	, MLWORD_cellpadding, MLWORD_cellspacing, MLWORD_frameborder
	, MLWORD_marginwidth, MLWORD_onmousedown, MLWORD_onmousemove

	, MLWORD_marginheight

	, MLWORD_accept_charset

	// HTML 5
	
	, MLWORD_wbr, MLWORD_spellcheck

	// XHTML

	, MLWORD_role

	// WAI-ARIA
	
	, MLWORD_aria_label, MLWORD_aria_owns, MLWORD_aria_owner
	, MLWORD_aria_haspopup

	// Non-standard HTML words
	
	, MLWORD_nobr, MLWORD_sig, MLWORD_topmargin
};

struct ml_dom_attribute
{
	enum ml_word id;
	const uint8_t* nstart;
	const uint8_t* nend;
	const uint8_t* vstart;
	const uint8_t* vend;
	struct ml_dom_attribute* next;
};

enum ml_dom_content_type
{
	MLDOM_CONTENT_ELEMENT
	, MLDOM_CONTENT_TEXT
	, MLDOM_CONTENT_SCRIPT
	, MLDOM_CONTENT_COMMENT
};

/* 
 * ml_dom_element is a dual structure. It may hold either an element
 * or a text node. It's done so to reduce the data structures count
 * and simplify the dom processing, paying with memory for the simplicity.
 */
struct ml_dom_element
{
	/* The type of a struct content. */
	enum ml_dom_content_type type;

	/* The id of an element defined by some standard. This makes
	 * sense only if a struct holds an element. */
	enum ml_word id;

	/* If the struct holds a dom element
	 * the start and the end fields define it's name,
	 * otherwise they define a text borders.
	 */
	const uint8_t* start;
	const uint8_t* end;

	/* attributes */
	struct {
		struct ml_dom_attribute* head;
		struct ml_dom_attribute* tail;
	} alist;

	/* content */
	struct {
		struct ml_dom_element* head;
		struct ml_dom_element* tail;
	} clist;

	struct ml_dom_element* next;
};

struct ml_dom
{
	struct ml_dom_element* document;
	struct ml_dom_data *data;
};

#define MLDOM_ELEMENT_INIT(element, s, e, a, t) do {			\
	(element)->type = t;						\
	(element)->id = MLWORD_UNKNOWN;					\
	(element)->start = s;						\
	(element)->end = e;						\
	(element)->alist.head = NULL;					\
	(element)->alist.tail = NULL;					\
	(element)->clist.head = NULL;					\
	(element)->clist.tail = NULL;					\
	(element)->next = NULL;						\
} while (0)

#define MLDOM_ELEMENT_ADD_ATTRIBUTE(element, attribute) do {		\
	if ((element)->alist.head != NULL) {				\
		(element)->alist.tail->next = (attribute);		\
	} else {							\
		(element)->alist.head = (attribute);			\
	}								\
	(element)->alist.tail = (attribute);				\
} while (0)

#define MLDOM_ELEMENT_ADD_CONTENT(element, content) do {		\
	if ((element)->clist.head != NULL) {				\
		(element)->clist.tail->next = (content);		\
	} else {							\
		(element)->clist.head = (content);			\
	}								\
	(element)->clist.tail = (content);				\
} while (0)

void mld_print_dom_attribute(FILE* f, int level, struct ml_dom_attribute* attribute);
void mld_print_dom_element(FILE* f, int level, struct ml_dom_element*);
void mld_print_dom_text(FILE* f, int level, struct ml_dom_element* text);
void mld_print_dom_script(FILE* f, int level, struct ml_dom_element* script);
void mld_print_dom_comment(FILE* f, int level, struct ml_dom_element* comment);
void mld_print_dom_element_tree(FILE* f, int level, struct ml_dom_element* root);
void mld_print_dom_text_tree(FILE* f, int level, struct ml_dom_element* root);
void mld_print_dom(FILE* f, struct ml_dom* dom);
void mld_print_text(FILE* f, struct ml_dom* dom);

#endif

