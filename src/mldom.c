#include "mldom.h"

const char* tab = "    ";

static inline indent(FILE* f, int level)
{
	int i;
	for(i = 0; i < level; ++i)
		fprintf(f, tab);
}

static inline printstr(FILE* f, int level
		, const uint8_t* start, const uint8_t* end
		, const char* prefix, const char* postfix)
{
	indent(f, level);
	printf("%s", prefix);
	const uint8_t *s = start;
	while (s != end) {
		fprintf(f, "%c", *s);
		if (*s == '\n')
			indent(f, level);
		s++;
	}
	printf("%s", postfix);
}

void mld_print_dom_attribute(FILE* f, int level, struct ml_dom_attribute* attribute)
{
	printstr(f, level, attribute->nstart, attribute->nend, "", ": ");
	printstr(f, 0, attribute->vstart, attribute->vend, "", "\n");
}

void mld_print_dom_element(FILE* f, int level, struct ml_dom_element* element)
{
	printstr(f, level, element->start, element->end, "<", "\n");
	
	struct ml_dom_attribute* attr;
	attr = element->alist.head;

	if (attr) {
		indent(f, level+1);
		fprintf(f, "attributes:\n");
		do {
			mld_print_dom_attribute(f, level + 2, attr);
			attr = attr->next;
		} while (attr);
	}
}

void mld_print_dom_element_tree(FILE* f, int level, struct ml_dom_element* element)
{
	struct ml_dom_element* child;
	switch (element->type) {

		case MLDOM_CONTENT_ELEMENT:
			mld_print_dom_element(f, level, element);
			child = element->clist.head;
			if (child) {
				indent(f, level + 1);
				fprintf(f, "children:\n");
				do {
					mld_print_dom_element_tree(f, level + 2, child);
					child = child->next;
				} while (child);
			}

			break;

		case MLDOM_CONTENT_TEXT:
			indent(f, level);
			fprintf(f, ":text:\n");
			printstr(f, level + 1, element->start, element->end, "", "\n");
			break;

		case MLDOM_CONTENT_SCRIPT:
			indent(f, level);
			fprintf(f, ":script:\n");
			printstr(f, level + 1, element->start, element->end, "", "\n");
			break;

		case MLDOM_CONTENT_COMMENT:
			indent(f, level);
			fprintf(f, ":comment:\n");
			printstr(f, level + 1, element->start, element->end, "", "\n");
			break;
	}
}

void mld_print_dom_text_tree(FILE* f, int level, struct ml_dom_element* element)
{
	struct ml_dom_element* child;
	switch (element->type) {

		case MLDOM_CONTENT_ELEMENT:
			if (child = element->clist.head) do {
					mld_print_dom_text_tree(f, level + 2, child);
			} while (child = child->next);
			break;

		case MLDOM_CONTENT_TEXT:
			printstr(f, level + 1, element->start, element->end, "", "");
			break;
	}
}

void mld_print_dom(FILE* f, struct ml_dom* dom)
{
	mld_print_dom_element_tree(f, 0, dom->document);
}

void mld_print_text(FILE* f, struct ml_dom* dom)
{
	mld_print_dom_text_tree(f, 0, dom->document);
}

