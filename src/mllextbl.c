
static struct asciiprop{
	unsigned int isalpha: 1;	// 0:
	unsigned int isdigit: 1;	// 1:
	unsigned int isspace: 1;	// 2:
	unsigned int islccontent: 1;	// 3:
	unsigned int isvspace: 1;	// 4:
	unsigned int ishexdigit: 1;	// 5:
	unsigned int isuri: 1;		// 6:
	unsigned int prop7: 1;		// 7:
	unsigned int prop8: 1;		// 8:
	unsigned int prop9: 1;		// 9:
	unsigned int prop10: 1;		// 10:
	unsigned int prop11: 1;		// 11:
	unsigned int prop12: 1;		// 12:
	unsigned int prop13: 1;		// 13:
	unsigned int isibody: 1;	// 14: ml identifier body [a-zA-Z0-9_-]
	unsigned int isistart: 1;	// 15: ml identifier start [a-zA-Z_]
	enum ml_error (*parse)(struct ml_lex_ctxt* l, struct ml_token* t);
} ascii[] = {
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 0
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 1
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 2
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 3
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 4
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 5
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 6
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 7
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 8
	, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_space } // 9: horizontal tab
	, { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_space } // 10: new line
	, { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_space } // 11: vertical tab
	, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_space } // 12: form feed
	, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_space } // 13: carriage return
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 14
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 15
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 16
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 17
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 18
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 19
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 20
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 21
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 22
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 23
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 24
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 25
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 26
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 27
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 28
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 29
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 30
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 31
	, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_space } // 32: space
	, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 33: !
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_double_quoted_string } // 34: "
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_rgb_value } // #
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 36
	, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 37: %
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 38
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_single_quoted_string } // 39: '
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 40
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 41
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 42
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 43
	, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 44: ,
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 45: -
	, { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 46: .
	, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_slash } // 47: /
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 48: 0
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 49: 1
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 50: 2
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 51: 3
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 52: 4
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 53: 5
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 54: 6
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 55: 7
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 56: 8
	, { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_measure } // 57: 9
	, { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, ml_ascii_symbol } // 58: :
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 59
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_lt } // 60: <
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_eq } // 61: =
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_gt } // 62: >
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_proc_instr_closer } // 63: ?
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 64
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 65: A
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 66: B
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 67: C
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 68: D
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 69: E
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 70: F
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 71: G
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 72: H
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 73: I
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 74: J
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 75: K
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 76: L
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 77: M
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 78: N
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 79: O
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 80: P
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 81: Q
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 82: R
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 83: S
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 84: T
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 85: U
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 86: V
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 87: W
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 88: X
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 89: Y
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 90: Z
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 91
	, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 92 '\'
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 93
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 94
	, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_ascii_symbol } // 95: _
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 96
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 97: a
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 98: b
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 99: c
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 100: d
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 101: e
	, { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 102: f
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 103: g
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 104: h
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 105: i
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 106: j
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 107: k
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 108: l
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 109: m
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 110: n
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 111: o
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 112: p
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 113: q
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 114: r
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 115: s
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 116: t
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 117: u
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 118: v
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 119: w
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 120: x
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 121: y
	, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, ml_identifier } // 122: z
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 123
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 124
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 125
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 126
	, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ml_ascii_symbol } // 127
};

static ssize_t transition [MLMAX_STATE][MLMAX_TOKEN_TYPE]; 

static inline ssize_t ml_transition(enum ml_state_type state, enum ml_token_type type)
{
	switch (state)
	{
		case MLSTATE_INITIAL:
			switch (type)
			{
				case MLTOKEN_LT:
					return MLSTATE_START_TAG_OPENED;
				case MLTOKEN_DTD_OPENER:
					return MLSTATE_DTD_OPENED;
				case MLTOKEN_PROC_INSTR_OPENER:
					return MLSTATE_PROC_INSTR_OPENED;
				case MLTOKEN_END_TAG_OPENER:
					return MLSTATE_END_TAG_OPENED;
				default:
					return MLSTATE_INITIAL;
			}
		case MLSTATE_DTD_OPENED:
			switch (type)
			{
				case MLTOKEN_GT:
					return MLSTATE_INITIAL;
				default:
					return MLSTATE_DTD_OPENED;
			}
		case MLSTATE_PROC_INSTR_OPENED:
			switch (type)
			{
				case MLTOKEN_PROC_INSTR_CLOSER:
					return MLSTATE_INITIAL;
				default:
					return MLSTATE_PROC_INSTR_OPENED;
			}
		case MLSTATE_START_TAG_OPENED:
			switch (type)
			{
				case MLTOKEN_IDENTIFIER:
					return MLSTATE_ELEMENT_IDENTIFIED;
				default:
					return MLSTATE_START_TAG_OPENED;
			}
		case MLSTATE_ELEMENT_IDENTIFIED:
			switch (type)
			{
				case MLTOKEN_START_TAG_CLOSER:
					return MLSTATE_INITIAL;
				case MLTOKEN_GT:
					return MLSTATE_ELEMENT_OPENED;
				case MLTOKEN_EQ:
					return MLSTATE_ATTR_EQ_FOUND;
				case MLTOKEN_SINGLE_QUOTED_STRING:
				case MLTOKEN_DOUBLE_QUOTED_STRING:
				case MLTOKEN_CCONTENT:
				case MLTOKEN_LCCONTENT:
					return MLSTATE_ATTR_VALUE_FOUND;
				default:
					return MLSTATE_ELEMENT_IDENTIFIED;
			}
		case MLSTATE_ATTR_EQ_FOUND:
			switch (type)
			{
				case MLTOKEN_SINGLE_QUOTED_STRING:
				case MLTOKEN_DOUBLE_QUOTED_STRING:
				case MLTOKEN_CCONTENT:
				case MLTOKEN_LCCONTENT:
				case MLTOKEN_IDENTIFIER:
				case MLTOKEN_MEASURE:
				case MLTOKEN_RGB_VALUE:
					return MLSTATE_ATTR_VALUE_FOUND;
				default:
					return MLSTATE_ATTR_EQ_FOUND;
			}
		case MLSTATE_ATTR_VALUE_FOUND:
			switch (type)
			{
				case MLTOKEN_START_TAG_CLOSER:
					return MLSTATE_INITIAL;
				case MLTOKEN_GT:
					return MLSTATE_ELEMENT_OPENED;
				case MLTOKEN_EQ:
					return MLSTATE_ATTR_EQ_FOUND;
				case MLTOKEN_SINGLE_QUOTED_STRING:
				case MLTOKEN_DOUBLE_QUOTED_STRING:
				case MLTOKEN_CCONTENT:
				case MLTOKEN_LCCONTENT:
					return MLSTATE_ATTR_VALUE_FOUND;
				case MLTOKEN_IDENTIFIER:
					return MLSTATE_ELEMENT_IDENTIFIED;
				default:
					return MLSTATE_ATTR_VALUE_FOUND;
			}
		case MLSTATE_ELEMENT_OPENED:
			switch (type)
			{
				case MLTOKEN_LT:
					return MLSTATE_START_TAG_OPENED;
				case MLTOKEN_DTD_OPENER:
					return MLSTATE_DTD_OPENED;
				case MLTOKEN_CCONTENT:
				case MLTOKEN_LCCONTENT:
					return MLSTATE_ELEMENT_CONTENT_FOUND;
				case MLTOKEN_END_TAG_OPENER:
					return MLSTATE_END_TAG_OPENED;
				default:
					return MLSTATE_INITIAL;
			}
		case MLSTATE_ELEMENT_CONTENT_FOUND:
			switch (type)
			{
				case MLTOKEN_DTD_OPENER:
					return MLSTATE_DTD_OPENED;
				case MLTOKEN_LT:
					return MLSTATE_START_TAG_OPENED;
				case MLTOKEN_END_TAG_OPENER:
					return MLSTATE_END_TAG_OPENED;
				default:
					return MLSTATE_INITIAL;
			}
		case MLSTATE_END_TAG_OPENED:
			switch (type)
			{
				case MLTOKEN_IDENTIFIER:
					return MLSTATE_END_TAG_IDENTIFIER_FOUND;
				default:
					return MLSTATE_END_TAG_OPENED;
			}
		case MLSTATE_END_TAG_IDENTIFIER_FOUND:
			switch (type)
			{
				case MLTOKEN_GT:
					return MLSTATE_INITIAL;
				default:
					return MLSTATE_END_TAG_IDENTIFIER_FOUND;
			}
	}

	return MLSTATE_INITIAL;
}

static inline void ml_fill_transition_table()
{
	int i, j;

	for (i = 0; i <=MLMAX_STATE; ++i)
		for (j = 0; j <= MLMAX_TOKEN_TYPE; ++j)
			transition[i][j] = ml_transition(i, j);
}

enum ml_word ml_string2tag(const uint8_t* start, const uint8_t* end)
{
	int sz = end - start;

	switch (sz)
	{
		case 0: return MLWORD_UNKNOWN;

		case 1: switch (start[0]) {
			case 'a': case 'A': return MLWORD_a;
			case 'b': case 'B': return MLWORD_b;
			case 'i': case 'I': return MLWORD_i;
			case 'p': case 'P': return MLWORD_p;
			case 'q': case 'Q': return MLWORD_i;
			case 's': case 'S': return MLWORD_i;
			case 'u': case 'U': return MLWORD_u;
		}

		case 2: switch (start[0]) {
			case 'b': case 'B': switch (start[1]) {
				case 'R': case 'r': return MLWORD_br;
			}
			case 'd': case 'D': switch (start[1]) {
				case 'd': case 'D': return MLWORD_dd;
				case 'l': case 'L': return MLWORD_dl;
				case 't': case 'T': return MLWORD_dt;
			}
			case 'e': case 'E': switch (start[1]) {
				case 'm': case 'M': return MLWORD_em;
			}
			case 'h': case 'H': switch (start[1]) {
				case '1': return MLWORD_h1;
				case '2': return MLWORD_h2;
				case '3': return MLWORD_h3;
				case '4': return MLWORD_h4;
				case '5': return MLWORD_h5;
				case '6': return MLWORD_h6;
				case 'r': case 'R': return MLWORD_hr;
			}
			case 'i': case 'I': switch (start[1]) {
				case 'd': case 'D': return MLWORD_id;
			}
			case 'l': case 'L': switch (start[1]) {
				case 'i': case 'I': return MLWORD_li;
			}
			case 'o': case 'O': switch (start[1]) {
				case 'l': case 'L': return MLWORD_ol;
			}
			case 't': case 'T': switch (start[1]) {
				case 'd': case 'D': return MLWORD_td;
				case 'h': case 'H': return MLWORD_th;
				case 'r': case 'R': return MLWORD_tr;
				case 't': case 'T': return MLWORD_tt;
			}
			case 'u': case 'U': switch (start[1]) {
				case 'l': case 'L': return MLWORD_ul;
			}
		}

		case 3: switch (start[0]) {
			case 'a': case 'A': switch (start[1]) {
				case 'l': case 'L': switch (start[2]) {
					case 't': case 'T': return MLWORD_alt;
				}
			}
			case 'b': case 'B': switch (start[1]) {
				case 'i': case 'I': switch (start[2]) {
					case 'g': case 'G': return MLWORD_big;
				}
				case 'd': case 'D': switch (start[2]) {
					case 'o': case 'O': return MLWORD_bdo;
				}
			}
			case 'c': case 'C': switch (start[1]) {
				case 'o': case 'O': switch (start[2]) {
					case 'l': case 'L': return MLWORD_col;
				}
			}
			case 'd': case 'D': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'l': case 'L': return MLWORD_del;
				}
				case 'f': case 'F': switch (start[2]) {
					case 'n': case 'N': return MLWORD_dfn;
				}
				case 'i': case 'I': switch (start[2]) {
					case 'r': case 'R': return MLWORD_dir;
					case 'v': case 'V': return MLWORD_div;
				}
			}
			case 'f': case 'F': switch (start[1]) {
				case 'o': case 'O': switch (start[2]) {
					case 'r': case 'R': return MLWORD_for;
				}
			}
			case 'i': case 'I': switch (start[1]) {
				case 'm': case 'M': switch (start[2]) {
					case 'g': case 'G': return MLWORD_img;
				}
				case 'n': case 'N': switch (start[2]) {
					case 's': case 'S': return MLWORD_ins;
				}
			}
			case 'k': case 'K': switch (start[1]) {
				case 'b': case 'B': switch (start[2]) {
					case 'd': case 'D': return MLWORD_kbd;
				}
			}
			case 'm': case 'M': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'p': case 'P': return MLWORD_map;
				}
			}
			case 'p': case 'P': switch (start[1]) {
				case 'r': case 'R': switch (start[2]) {
					case 'e': case 'E': return MLWORD_pre;
				}
			}
			case 'r': case 'R': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'l': case 'L': return MLWORD_rel;
					case 'v': case 'V': return MLWORD_rev;
				}
			}
			case 's': case 'S': switch (start[1]) {
				case 'i': case 'I': switch (start[2]) {
					case 'g': case 'G': return MLWORD_sig;
				}
				case 'u': case 'U': switch (start[2]) {
					case 'b': case 'B': return MLWORD_sub;
					case 'p': case 'P': return MLWORD_sup;
				}
				case 'r': case 'R': switch (start[2]) {
					case 'c': case 'C': return MLWORD_src;
				}
			}
			case 'v': case 'V': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'r': case 'R': return MLWORD_var;
				}
			}
			case 'w': switch (start[1]) {
				case 'b': switch (start[2]) {
					case 'r': return MLWORD_wbr;
				}
			}
		}

		case 4: switch (start[0]) {
			case 'a': case 'A': switch (start[1]) {
				case 'b': case 'B': switch (start[2]) {
					case 'b': case 'B': switch (start[3]) {
						case 'r': case 'R': return MLWORD_abbr;
					}
				}
				case 'r': case 'R': switch (start[2]) {
					case 'e': case 'E': switch (start[3]) {
						case 'a': case 'A': return MLWORD_area;
					}
				}
				case 'x': case 'X': switch (start[2]) {
					case 'i': case 'I': switch (start[3]) {
						case 's': case 'S': return MLWORD_axis;
					}
				}
			}
			case 'b': case 'B': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 's': case 'S': switch (start[3]) {
						case 'e': case 'E': return MLWORD_base;
					}
				}
				case 'o': case 'O': switch (start[2]) {
					case 'd': case 'D': switch (start[3]) {
						case 'y': case 'Y': return MLWORD_body;
					}
				}
			}
			case 'c': case 'C': switch (start[1]) {
				case 'h': case 'H': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'r': case 'R': return MLWORD_char;
					}
				}
				case 'i': case 'I': switch (start[2]) {
					case 't': case 'T': switch (start[3]) {
						case 'e': case 'E': return MLWORD_cite;
					}
				}
				case 'o': case 'O': switch (start[2]) {
					case 'd': case 'D': switch (start[3]) {
						case 'e': case 'E': return MLWORD_code;
					}
					case 'l': case 'L': switch (start[3]) {
						case 's': case 'S': return MLWORD_cols;
					}
				}
			}
			case 'd': case 'D': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 't': case 'T': switch (start[3]) {
						case 'a': case 'A': return MLWORD_data;
					}
				}
			}
			case 'f': case 'F': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'e': case 'E': return MLWORD_face;
					}
				}
				case 'o': case 'O': switch (start[2]) {
					case 'n': case 'N': switch (start[3]) {
						case 't': case 'T': return MLWORD_font;
					}
					case 'r': case 'R': switch (start[3]) {
						case 'm': case 'M': return MLWORD_form;
					}
				}
			}
			case 'h': case 'H': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'd': case 'D': return MLWORD_head;
					}
				}
				case 'r': case 'R': switch (start[2]) {
					case 'e': case 'E': switch (start[3]) {
						case 'f': case 'F': return MLWORD_href;
					}
				}
				case 't': case 'T': switch (start[2]) {
					case 'm': case 'M': switch (start[3]) {
						case 'l': case 'L': return MLWORD_html;
					}
				}
			}
			case 'l': case 'L': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'n': case 'N': switch (start[3]) {
						case 'g': case 'G': return MLWORD_lang;
					}
				}
				case 'i': case 'I': switch (start[2]) {
					case 'n': case 'N': switch (start[3]) {
						case 'k': case 'K': return MLWORD_link;
					}
				}
			}
			case 'm': case 'M': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'n': case 'N': switch (start[3]) {
						case 'u': case 'U': return MLWORD_menu;
					}
					case 't': case 'T': switch (start[3]) {
						case 'a': case 'A': return MLWORD_meta;
					}
				}
			}
			case 'n': case 'N': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'm': case 'M': switch (start[3]) {
						case 'e': case 'E': return MLWORD_name;
					}
				}
				case 'o': case 'O': switch (start[2]) {
					case 'b': case 'B': switch (start[3]) {
						case 'r': case 'R': return MLWORD_nobr;
					}
				}
			}
			case 'r': case 'R': switch (start[1]) {
				case 'o': case 'O': switch (start[2]) {
					case 'w': case 'W': switch (start[3]) {
						case 's': case 'S': return MLWORD_rows;
					}
					case 'l': case 'L': switch (start[3]) {
						case 'e': case 'E': return MLWORD_role;
					}
				}
			}
			case 's': case 'S': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'm': case 'M': switch (start[3]) {
						case 'p': case 'P': return MLWORD_samp;
					}
				}
				case 'i': case 'I': switch (start[2]) {
					case 'z': case 'Z': switch (start[3]) {
						case 'e': case 'E': return MLWORD_size;
					}
				}
				case 'p': case 'P': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'n': case 'N': return MLWORD_span;
					}
				}
			}
			case 't': case 'T': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'x': case 'X': switch (start[3]) {
						case 't': case 'T': return MLWORD_text;
					}
				}
				case 'y': case 'Y': switch (start[2]) {
					case 'p': case 'P': switch (start[3]) {
						case 'e': case 'E': return MLWORD_type;
					}
				}
			}
		}

		case 5: switch (start[0]) {
			case 'a': case 'A': switch (start[1]) {
				case 'l': case 'L': switch (start[2]) {
					case 'i': case 'I': switch (start[3]) {
						case 'g': case 'G': switch (start[4]) {
							case 'n': case 'N': return MLWORD_align;
						}
						case 'n': case 'N': switch (start[4]) {
							case 'k': case 'K': return MLWORD_alink;
						}
					}
				}
			}
			case 'c': case 'C': switch (start[1]) {
				case 'l': case 'L': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 's': case 'S': switch (start[4]) {
							case 's': case 'S': return MLWORD_class;
						}
					}
					case 'e': case 'E': switch (start[3]) {
						case 'a': case 'A': switch (start[4]) {
							case 'r': case 'R': return MLWORD_clear;
						}
					}
				}
				case 'o': case 'O': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 'r': case 'R': return MLWORD_color;
						}
					}
				}
			}
			case 'd': case 'D': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'f': case 'F': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'r': case 'R': return MLWORD_defer;
						}
					}
				}
			}
			case 'f': case 'F': switch (start[1]) {
				case 'r': case 'R': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'm': case 'M': switch (start[4]) {
							case 'e': case 'E': return MLWORD_frame;
						}
					}
				}
			}
			case 'i': case 'I': switch (start[1]) {
				case 'n': case 'N': switch (start[2]) {
					case 'p': case 'P': switch (start[3]) {
						case 'u': case 'U': switch (start[4]) {
							case 't': case 'T': return MLWORD_input;
						}
					}
				}
				case 's': case 'S': switch (start[2]) {
					case 'm': case 'M': switch (start[3]) {
						case 'a': case 'A': switch (start[4]) {
							case 'p': case 'P': return MLWORD_ismap;
						}
					}
				}
			}
			case 'l': case 'L': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'b': case 'B': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'l': case 'L': return MLWORD_label;
						}
					}
				}
			}
			case 'm': case 'M': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'd': case 'D': switch (start[3]) {
						case 'i': case 'I': switch (start[4]) {
							case 'a': case 'A': return MLWORD_media;
						}
					}
				}
			}
			case 'p': case 'P': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 'a': case 'A': switch (start[4]) {
							case 'm': case 'M': return MLWORD_param;
						}
					}
				}
			}
			case 'r': case 'R': switch (start[1]) {
				case 'u': case 'U': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 's': case 'S': return MLWORD_rules;
						}
					}
				}
			}
			case 's': case 'S': switch (start[1]) {
				case 'c': case 'C': switch (start[2]) {
					case 'o': case 'O': switch (start[3]) {
						case 'p': case 'P': switch (start[4]) {
							case 'e': case 'E': return MLWORD_scope;
						}
					}
				}
				case 'h': case 'H': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'p': case 'P': switch (start[4]) {
							case 'e': case 'E': return MLWORD_shape;
						}
					}
				}
				case 'm': case 'M': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'l': case 'L': return MLWORD_small;
						}
					}
				}
				case 't': case 'T': switch (start[2]) {
					case 'y': case 'Y': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'e': case 'E': return MLWORD_style;
						}
					}
					case 'a': case 'A': switch (start[3]) {
						case 'r': case 'R': switch (start[4]) {
							case 't': case 'T': return MLWORD_start;
						}
					}
				}
			}
			case 't': case 'T': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'b': case 'B': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'e': case 'E': return MLWORD_table;
						}
					}
				}
				case 'b': case 'B': switch (start[2]) {
					case 'o': case 'O': switch (start[3]) {
						case 'd': case 'D': switch (start[4]) {
							case 'y': case 'Y': return MLWORD_tbody;
						}
					}
				}
				case 'f': case 'F': switch (start[2]) {
					case 'o': case 'O': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 't': case 'T': return MLWORD_tfoot;
						}
					}
				}
				case 'h': case 'H': switch (start[2]) {
					case 'e': case 'E': switch (start[3]) {
						case 'a': case 'A': switch (start[4]) {
							case 'd': case 'D': return MLWORD_thead;
						}
					}
				}
				case 'i': case 'I': switch (start[2]) {
					case 't': case 'T': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'e': case 'E': return MLWORD_title;
						}
					}
				}
			}
			case 'v': case 'V': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 'u': case 'U': switch (start[4]) {
							case 'e': case 'E': return MLWORD_value;
						}
					}
				}
				case 'l': case 'L': switch (start[2]) {
					case 'i': case 'I': switch (start[3]) {
						case 'n': case 'N': switch (start[4]) {
							case 'k': case 'K': return MLWORD_vlink;
						}
					}
				}
			}
			case 'w': case 'W': switch (start[1]) {
				case 'i': case 'I': switch (start[2]) {
					case 'd': case 'D': switch (start[3]) {
						case 't': case 'T': switch (start[4]) {
							case 'h': case 'H': return MLWORD_width;
						}
					}
				}
			}
		}

		case 6: switch (start[0]) {
			case 'a': case 'A': switch (start[1]) {
				case 'p': case 'P': switch (start[2]) {
					case 'p': case 'P': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 't': case 'T': return MLWORD_applet;
							}
						}
					}
				}
				case 'c': case 'C': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'p': case 'P': switch (start[5]) {
								case 't': case 'T': return MLWORD_accept;
							}
						}
					}
					case 't': case 'T': switch (start[3]) {
						case 'i': case 'I': switch (start[4]) {
							case 'o': case 'O': switch (start[5]) {
								case 'n': case 'N': return MLWORD_action;
							}
						}
					}
				}
			}
			case 'b': case 'B': switch (start[1]) {
				case 'u': case 'U': switch (start[2]) {
					case 't': case 'T': switch (start[3]) {
						case 't': case 'T': switch (start[4]) {
							case 'o': case 'O': switch (start[5]) {
								case 'n': case 'N': return MLWORD_button;
							}
						}
					}
				}
				case 'o': case 'O': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 'd': case 'D': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 'r': case 'R': return MLWORD_border;
							}
						}
					}
				}
			}
			case 'c': case 'C': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'n': case 'N': switch (start[3]) {
						case 't': case 'T': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 'r': case 'R': return MLWORD_center;
							}
						}
					}
				}
				case 'o': case 'O': switch (start[2]) {
					case 'o': case 'O': switch (start[3]) {
						case 'r': case 'R': switch (start[4]) {
							case 'd': case 'D': switch (start[5]) {
								case 's': case 'S': return MLWORD_coords;
							}
						}
					}
				}
			}
			case 'h': case 'H': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'i': case 'I': switch (start[3]) {
						case 'g': case 'G': switch (start[4]) {
							case 'h': case 'H': switch (start[5]) {
								case 't': case 'T': return MLWORD_height;
							}
						}
					}
				}
				case 's': case 'S': switch (start[2]) {
					case 'p': case 'P': switch (start[3]) {
						case 'a': case 'A': switch (start[4]) {
							case 's': case 'S': switch (start[5]) {
								case 'e': case 'E': return MLWORD_hspace;
							}
						}
					}
				}
			}
			case 'i': case 'I': switch (start[1]) {
				case 'f': case 'F': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 'a': case 'A': switch (start[4]) {
							case 'm': case 'M': switch (start[5]) {
								case 'e': case 'E': return MLWORD_iframe;
							}
						}
					}
				}
			}
			case 'l': case 'L': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'g': case 'G': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'n': case 'N': switch (start[5]) {
								case 'd': case 'D': return MLWORD_legend;
							}
						}
					}
				}
			}
			case 'm': case 'M': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 't': case 'T': switch (start[3]) {
						case 'h': case 'H': switch (start[4]) {
							case 'o': case 'O': switch (start[5]) {
								case 'd': case 'D': return MLWORD_method;
							}
						}
					}
				}
			}
			case 'n': case 'N': switch (start[1]) {
				case 'o': case 'O': switch (start[2]) {
					case 'h': case 'H': switch (start[3]) {
						case 'r': case 'R': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 'f': case 'F': return MLWORD_nohref;
							}
						}
					}
					case 'w': case 'W': switch (start[3]) {
						case 'r': case 'R': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'p': case 'P': return MLWORD_nowrap;
							}
						}
					}
				}
			}
			case 'o': case 'O': switch (start[1]) {
				case 'b': case 'B': switch (start[2]) {
					case 'j': case 'J': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'c': case 'C': switch (start[5]) {
								case 't': case 'T': return MLWORD_object;
							}
						}
					}
				}
				case 'n': case 'N': switch (start[2]) {
					case 'b': case 'B': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'u': case 'U': switch (start[5]) {
								case 'r': case 'R': return MLWORD_onblur;
							}
						}
					}
					case 'l': case 'L': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'd': case 'A': return MLWORD_onload;
							}
						}
					}
				}
				case 'p': case 'P': switch (start[2]) {
					case 't': case 'T': switch (start[3]) {
						case 'i': case 'I': switch (start[4]) {
							case 'o': case 'O': switch (start[5]) {
								case 'n': case 'N': return MLWORD_option;
							}
						}
					}
				}
			}
			case 'p': case 'P': switch (start[1]) {
				case 'r': case 'R': switch (start[2]) {
					case 'o': case 'O': switch (start[3]) {
						case 'm': case 'M': switch (start[4]) {
							case 'p': case 'P': switch (start[5]) {
								case 't': case 'T': return MLWORD_prompt;
							}
						}
					}
				}
				case 'u': case 'U': switch (start[2]) {
					case 'b': case 'B': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'i': case 'I': switch (start[5]) {
								case 'c': case 'C': return MLWORD_PUBLIC;
							}
						}
					}
				}
			}
			case 's': case 'S': switch (start[1]) {
				case 'c': case 'C': switch (start[2]) {
					case 'h': case 'H': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'm': case 'M': switch (start[5]) {
								case 'e': case 'E': return MLWORD_script;
							}
						}
					}
					case 'r': case 'R': switch (start[3]) {
						case 'i': case 'I': switch (start[4]) {
							case 'p': case 'P': switch (start[5]) {
								case 't': case 'T': return MLWORD_script;
							}
						}
					}
				}
				case 'e': case 'E': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'c': case 'C': switch (start[5]) {
								case 't': case 'T': return MLWORD_select;
							}
						}
					}
				}
				case 't': case 'T': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 'i': case 'I': switch (start[4]) {
							case 'k': case 'K': switch (start[5]) {
								case 'e': case 'E': return MLWORD_strike;
							}
						}
						case 'o': case 'O': switch (start[4]) {
							case 'n': case 'N': switch (start[5]) {
								case 'g': case 'G': return MLWORD_strong;
							}
						}
					}
				}
			}
			case 't': case 'T': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 'g': case 'G': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 't': case 'T': return MLWORD_target;
							}
						}
					}
				}
			}
			case 'u': case 'U': switch (start[1]) {
				case 's': case 'S': switch (start[2]) {
					case 'e': case 'E': switch (start[3]) {
						case 'm': case 'M': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'p': case 'P': return MLWORD_usemap;
							}
						}
					}
				}
			}
			case 'v': case 'V': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 'i': case 'I': switch (start[4]) {
							case 'g': case 'G': switch (start[5]) {
								case 'n': case 'N': return MLWORD_valign;
							}
						}
					}
				}
				case 's': case 'S': switch (start[2]) {
					case 'p': case 'P': switch (start[3]) {
						case 'a': case 'A': switch (start[4]) {
							case 'c': case 'C': switch (start[5]) {
								case 'e': case 'E': return MLWORD_vspace;
							}
						}
					}
				}
			}
		}

		case 7: switch (start[0]) {
			case 'a': case 'A': switch (start[1]) {
				case 'c': case 'C': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 'n': case 'N': switch (start[5]) {
								case 'y': case 'Y': switch (start[6]) {
									case 'm': case 'M': return MLWORD_acronym;
								}
							}
						}
					}
				}
				case 'r': case 'R': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'h': case 'H': switch (start[4]) {
							case 'i': case 'I': switch (start[5]) {
								case 'v': case 'V': switch (start[6]) {
									case 'e': case 'E': return MLWORD_archive;
								}
							}
						}
					}
				}
			}
			case 'b': case 'B': switch (start[1]) {
				case 'g': case 'G': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 'l': case 'L': switch (start[5]) {
								case 'o': case 'O': switch (start[6]) {
									case 'r': case 'R': return MLWORD_bgcolor;
								}
							}
						}
					}
				}
			}
			case 'c': case 'C': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'p': case 'P': switch (start[3]) {
						case 't': case 'T': switch (start[4]) {
							case 'i': case 'I': switch (start[5]) {
								case 'o': case 'O': switch (start[6]) {
									case 'n': case 'N': return MLWORD_caption;
								}
							}
						}
					}
				}
				case 'l': case 'L': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 's': case 'S': switch (start[4]) {
							case 's': case 'S': switch (start[5]) {
								case 'i': case 'I': switch (start[6]) {
									case 'd': case 'D': return MLWORD_classid;
								}
							}
						}
					}
				}
				case 'h': case 'H': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'r': case 'R': switch (start[4]) {
							case 'o': case 'O': switch (start[5]) {
								case 'f': case 'F': switch (start[6]) {
									case 'f': case 'F': return MLWORD_charoff;
								}
							}
							case 's': case 'S': switch (start[5]) {
								case 'e': case 'E': switch (start[6]) {
									case 't': case 'T': return MLWORD_charset;
								}
							}
						}
					}
					case 'e': case 'E': switch (start[3]) {
						case 'c': case 'C': switch (start[4]) {
							case 'k': case 'K': switch (start[5]) {
								case 'e': case 'E': switch (start[6]) {
									case 'd': case 'D': return MLWORD_checked;
								}
							}
						}
					}
				}
				case 'o': case 'O': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 's': case 'S': switch (start[4]) {
							case 'p': case 'P': switch (start[5]) {
								case 'a': case 'A': switch (start[6]) {
									case 'n': case 'N': return MLWORD_colspan;
								}
							}
						}
					}
					case 'm': case 'M': switch (start[3]) {
						case 'p': case 'P': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'c': case 'C': switch (start[6]) {
									case 't': case 'T': return MLWORD_compact;
								}
							}
						}
					}
					case 'n': case 'N': switch (start[3]) {
						case 't': case 'T': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 'n': case 'N': switch (start[6]) {
									case 't': case 'T': return MLWORD_content;
								}
							}
						}
					}
				}
			}
			case 'd': case 'D': switch (start[1]) {
				case 'O': switch (start[2]) {
					case 'C': switch (start[3]) {
						case 'T': switch (start[4]) {
							case 'Y': switch (start[5]) {
								case 'P': switch (start[6]) {
									case 'E': return MLWORD_DOCTYPE;
								}
							}
						}
					}
				}
				case 'e': case 'E': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'r': case 'R': switch (start[6]) {
									case 'e': case 'E': return MLWORD_declare;
								}
							}
						}
					}
				}
			}
			case 'e': case 'E': switch (start[1]) {
				case 'n': case 'N': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 't': case 'T': switch (start[4]) {
							case 'y': case 'Y': switch (start[5]) {
								case 'p': case 'P': switch (start[6]) {
									case 'e': case 'E': return MLWORD_enctype;
								}
							}
						}
					}
				}
			}
			case 'h': case 'H': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'd': case 'D': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 'r': case 'R': switch (start[6]) {
									case 's': case 'S': return MLWORD_headers;
								}
							}
						}
					}
				}
			}
			case 'i': case 'I': switch (start[1]) {
				case 's': case 'S': switch (start[2]) {
					case 'i': case 'I': switch (start[3]) {
						case 'n': case 'N': switch (start[4]) {
							case 'd': case 'D': switch (start[5]) {
								case 'e': case 'E': switch (start[6]) {
									case 'x': case 'X': return MLWORD_isindex;
								}
							}
						}
					}
				}
			}
			case 'n': case 'N': switch (start[1]) {
				case 'o': case 'O': switch (start[2]) {
					case 's': case 'S': switch (start[3]) {
						case 'h': case 'H': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'd': case 'D': switch (start[6]) {
									case 'e': case 'E': return MLWORD_noshade;
								}
							}
						}
					}
				}
			}
			case 'o': case 'O': switch (start[1]) {
				case 'n': case 'N': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'i': case 'I': switch (start[5]) {
								case 'c': case 'C': switch (start[6]) {
									case 'k': case 'K': return MLWORD_onclick;
								}
							}
						}
					}
					case 'e': case 'E': switch (start[3]) {
						case 'r': case 'R': switch (start[4]) {
							case 'r': case 'R': switch (start[5]) {
								case 'o': case 'O': switch (start[6]) {
									case 'r': case 'R': return MLWORD_onerror;
								}
							}
						}
					}
					case 'f': case 'F': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 'c': case 'C': switch (start[5]) {
								case 'u': case 'U': switch (start[6]) {
									case 's': case 'S': return MLWORD_onfocus;
								}
							}
						}
					}
					case 'k': case 'K': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'y': case 'Y': switch (start[5]) {
								case 'u': case 'U': switch (start[6]) {
									case 'p': case 'P': return MLWORD_onkeyup;
								}
							}
						}
					}
					case 'r': case 'R': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 's': case 'S': switch (start[5]) {
								case 'e': case 'E': switch (start[6]) {
									case 't': case 'T': return MLWORD_onreset;
								}
							}
						}
					}
				}
			}
			case 'p': case 'P': switch (start[1]) {
				case 'r': case 'R': switch (start[2]) {
					case 'o': case 'O': switch (start[3]) {
						case 'f': case 'F': switch (start[4]) {
							case 'i': case 'I': switch (start[5]) {
								case 'l': case 'L': switch (start[6]) {
									case 'e': case 'E': return MLWORD_profile;
								}
							}
						}
					}
				}
			}
			case 'r': case 'R': switch (start[1]) {
				case 'o': case 'O': switch (start[2]) {
					case 'w': case 'W': switch (start[3]) {
						case 's': case 'S': switch (start[4]) {
							case 'p': case 'P': switch (start[5]) {
								case 'a': case 'A': switch (start[6]) {
									case 'n': case 'N': return MLWORD_rowspan;
								}
							}
						}
					}
				}
			}
			case 's': case 'S': switch (start[1]) {
				case 't': case 'T': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'n': case 'N': switch (start[4]) {
							case 'd': case 'D': switch (start[5]) {
								case 'b': case 'B': switch (start[6]) {
									case 'y': case 'Y': return MLWORD_standby;
								}
							}
						}
					}
				}
				case 'u': case 'U': switch (start[2]) {
					case 'm': case 'M': switch (start[3]) {
						case 'm': case 'M': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'r': case 'R': switch (start[6]) {
									case 'y': case 'Y': return MLWORD_summary;
								}
							}
						}
					}
				}
			}
			case 'v': case 'V': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 's': case 'S': switch (start[4]) {
							case 'i': case 'I': switch (start[5]) {
								case 'o': case 'O': switch (start[6]) {
									case 'n': case 'N': return MLWORD_version;
								}
							}
						}
					}
				}
			}
		}

		case 8: switch (start[0]) {
			case 'b': case 'B': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 's': case 'S': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'f': case 'F': switch (start[5]) {
								case 'o': case 'O': switch (start[6]) {
									case 'n': case 'N': switch (start[7]) {
										case 't': case 'T': return MLWORD_basefont;
									}
								}
							}
						}
					}
				}
			}
			case 'c': case 'C': switch (start[1]) {
				case 'o': case 'O': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 'g': case 'G': switch (start[4]) {
							case 'r': case 'R': switch (start[5]) {
								case 'o': case 'O': switch (start[6]) {
									case 'u': case 'U': switch (start[7]) {
										case 'p': case 'P': return MLWORD_colgroup;
									}
								}
							}
						}
					}
					case 'd': case 'D': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'b': case 'B': switch (start[5]) {
								case 'a': case 'A': switch (start[6]) {
									case 's': case 'S': switch (start[7]) {
										case 'e': case 'E': return MLWORD_codebase;
									}
								}
							}
							case 't': case 'T': switch (start[5]) {
								case 'y': case 'Y': switch (start[6]) {
									case 'p': case 'P': switch (start[7]) {
										case 'e': case 'E': return MLWORD_codetype;
									}
								}
							}
						}
					}
				}
			}
			case 'd': case 'D': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 't': case 'T': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 't': case 'T': switch (start[5]) {
								case 'i': case 'I': switch (start[6]) {
									case 'm': case 'M': switch (start[7]) {
										case 'e': case 'E': return MLWORD_datetime;
									}
								}
							}
						}
					}
				}
				case 'i': case 'I': switch (start[2]) {
					case 's': case 'S': switch (start[3]) {
						case 'a': case 'A': switch (start[4]) {
							case 'b': case 'B': switch (start[5]) {
								case 'l': case 'L': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 'd': case 'D': return MLWORD_disabled;
									}
								}
							}
						}
					}
				}
			}
			case 'f': case 'F': switch (start[1]) {
				case 'i': case 'I': switch (start[2]) {
					case 'e': case 'E': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'd': case 'D': switch (start[5]) {
								case 's': case 'S': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 't': case 'T': return MLWORD_fieldset;
									}
								}
							}
						}
					}
				}
				case 'r': case 'R': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'm': case 'M': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 's': case 'S': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 't': case 'T': return MLWORD_frame;
									}
								}
							}
						}
					}
				}
			}
			case 'h': case 'H': switch (start[1]) {
				case 'r': case 'R': switch (start[2]) {
					case 'e': case 'E': switch (start[3]) {
						case 'f': case 'F': switch (start[4]) {
							case 'l': case 'L': switch (start[5]) {
								case 'a': case 'A': switch (start[6]) {
									case 'n': case 'N': switch (start[7]) {
										case 'g': case 'G': return MLWORD_hreflang;
									}
								}
							}
						}
					}
				}
			}
			case 'l': case 'L': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'n': case 'N': switch (start[3]) {
						case 'g': case 'G': switch (start[4]) {
							case 'u': case 'U': switch (start[5]) {
								case 'a': case 'A': switch (start[6]) {
									case 'g': case 'G': switch (start[7]) {
										case 'e': case 'E': return MLWORD_language;
									}
								}
							}
						}
					}
				}
				case 'o': case 'O': switch (start[2]) {
					case 'n': case 'N': switch (start[3]) {
						case 'g': case 'G': switch (start[4]) {
							case 'd': case 'D': switch (start[5]) {
								case 'e': case 'E': switch (start[6]) {
									case 's': case 'S': switch (start[7]) {
										case 'c': case 'C': return MLWORD_longdesc;
									}
								}
							}
						}
					}
				}
			}
			case 'm': case 'M': switch (start[1]) {
				case 'u': case 'U': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 't': case 'T': switch (start[4]) {
							case 'i': case 'I': switch (start[5]) {
								case 'p': case 'P': switch (start[6]) {
									case 'l': case 'L': switch (start[7]) {
										case 'e': case 'E': return MLWORD_multiple;
									}
								}
							}
						}
					}
				}
			}
			case 'n': case 'N': switch (start[1]) {
				case 'o': case 'O': switch (start[2]) {
					case 'f': case 'F': switch (start[3]) {
						case 'r': case 'R': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'm': case 'M': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 's': case 'S': return MLWORD_noframes;
									}
								}
							}
						}
					}
					case 'r': case 'R': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 's': case 'S': switch (start[5]) {
								case 'i': case 'I': switch (start[6]) {
									case 'z': case 'Z': switch (start[7]) {
										case 'e': case 'E': return MLWORD_noresize;
									}
								}
							}
						}
					}
					case 's': case 'S': switch (start[3]) {
						case 'c': case 'C': switch (start[4]) {
							case 'r': case 'R': switch (start[5]) {
								case 'i': case 'I': switch (start[6]) {
									case 'p': case 'P': switch (start[7]) {
										case 't': case 'T': return MLWORD_noscript;
									}
								}
							}
						}
					}
				}
			}
			case 'o': case 'O': switch (start[1]) {
				case 'p': case 'P': switch (start[2]) {
					case 't': case 'T': switch (start[3]) {
						case 'g': case 'G': switch (start[4]) {
							case 'r': case 'R': switch (start[5]) {
								case 'o': case 'O': switch (start[6]) {
									case 'u': case 'U': switch (start[7]) {
										case 'p': case 'P': return MLWORD_optgroup;
									}
								}
							}
						}
					}
				}
				case 'n': case 'N': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'h': case 'H': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'n': case 'N': switch (start[6]) {
									case 'g': case 'G': switch (start[7]) {
										case 'e': case 'E': return MLWORD_onchange;
									}
								}
							}
						}
					}
					case 's': case 'S': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'l': case 'L': switch (start[5]) {
								case 'e': case 'E': switch (start[6]) {
									case 'c': case 'C': switch (start[7]) {
										case 't': case 'T': return MLWORD_onselect;
									}
								}
							}
						}
						case 'u': case 'U': switch (start[4]) {
							case 'b': case 'B': switch (start[5]) {
								case 'm': case 'M': switch (start[6]) {
									case 'i': case 'I': switch (start[7]) {
										case 't': case 'T': return MLWORD_onsubmit;
									}
								}
							}
						}
					}
					case 'u': case 'U': switch (start[3]) {
						case 'n': case 'N': switch (start[4]) {
							case 'l': case 'L': switch (start[5]) {
								case 'o': case 'O': switch (start[6]) {
									case 'a': case 'A': switch (start[7]) {
										case 'd': case 'D': return MLWORD_onunload;
									}
								}
							}
						}
					}
				}
			}
			case 'r': case 'R': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'd': case 'D': switch (start[4]) {
							case 'o': case 'O': switch (start[5]) {
								case 'n': case 'N': switch (start[6]) {
									case 'l': case 'L': switch (start[7]) {
										case 'y': case 'Y': return MLWORD_readonly;
									}
								}
							}
						}
					}
				}
			}
			case 's': case 'S': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'c': case 'C': switch (start[5]) {
								case 't': case 'T': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 'd': case 'D': return MLWORD_selected;
									}
								}
							}
						}
					}
				}
			}
			case 't': case 'T': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'b': case 'B': switch (start[3]) {
						case 'i': case 'I': switch (start[4]) {
							case 'n': case 'N': switch (start[5]) {
								case 'd': case 'D': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 'x': case 'X': return MLWORD_tabindex;
									}
								}
							}
						}
					}
				}
				case 'e': case 'E': switch (start[2]) {
					case 'x': case 'X': switch (start[3]) {
						case 't': case 'T': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'r': case 'R': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 'a': case 'A': return MLWORD_textarea;
									}
								}
							}
						}
					}
				}
			}
		}

		case 9: switch (start[0]) {
			case 'a': case 'A': switch (start[1]) {
				case 'r': switch (start[2]) {
					case 'i': switch (start[3]) {
						case 'a': switch (start[4]) {
							case '-': switch (start[5]) {
								case 'o': switch (start[6]) {
									case 'w': switch (start[7]) {
										case 'n': switch (start[8]) {
											case 's': return MLWORD_aria_owns;
										}
									}
								}
							}
						}
					}
				}
				case 'c': case 'C': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 's': case 'S': switch (start[5]) {
								case 's': case 'S': switch (start[6]) {
									case 'k': case 'K': switch (start[7]) {
										case 'e': case 'E': switch (start[8]) {
											case 'y': case 'Y': return MLWORD_accesskey;
										}
									}
								}
							}
						}
					}
				}
			}
			case 'm': case 'M': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'x': case 'X': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 'n': case 'N': switch (start[6]) {
									case 'g': case 'G': switch (start[7]) {
										case 't': case 'T': switch (start[8]) {
											case 'h': case 'H': return MLWORD_maxlength;
										}
									}
								}
							}
						}
					}
				}
			}
			case 'o': case 'O': switch (start[1]) {
				case 'n': case 'N': switch (start[2]) {
					case 'k': case 'K': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'y': case 'Y': switch (start[5]) {
								case 'd': case 'D': switch (start[6]) {
									case 'o': case 'O': switch (start[7]) {
										case 'w': case 'W': switch (start[8]) {
											case 'n': case 'N': return MLWORD_onkeydown;
										}
									}
								}
							}
						}
					}
					case 'm': case 'M': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 'u': case 'U': switch (start[5]) {
								case 's': case 'S': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 'u': case 'U': switch (start[8]) {
											case 'p': case 'P': return MLWORD_onmouseup;
										}
									}
								}
							}
						}
					}
				}
			}
			case 's': case 'S': switch (start[1]) {
				case 'c': case 'C': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 'l': case 'L': switch (start[5]) {
								case 'l': case 'L': switch (start[6]) {
									case 'i': case 'I': switch (start[7]) {
										case 'n': case 'N': switch (start[8]) {
											case 'g': case 'G': return MLWORD_scrolling;
										}
									}
								}
							}
						}
					}
				}
			}
			case 't': case 'T': switch (start[1]) {
				case 'o': case 'O': switch (start[2]) {
					case 'p': case 'P': switch (start[3]) {
						case 'm': case 'M': switch (start[4]) {
							case 'a': case 'A': switch (start[5]) {
								case 'r': case 'R': switch (start[6]) {
									case 'g': case 'G': switch (start[7]) {
										case 'i': case 'I': switch (start[8]) {
											case 'n': case 'N': return MLWORD_topmargin;
										}
									}
								}
							}
						}
					}
				}
			}
			case 'v': case 'V': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 'u': case 'U': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 't': case 'T': switch (start[6]) {
									case 'y': case 'Y': switch (start[7]) {
										case 'p': case 'P': switch (start[8]) {
											case 'e': case 'E': return MLWORD_valuetype;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		case 10: switch (start[0]) {
			case 'a': switch (start[1]) {
				case 'r': switch (start[2]) {
					case 'i': switch (start[3]) {
						case 'a': switch (start[4]) {
							case '-': switch (start[5]) {
								case 'l': switch (start[6]) {
									case 'a': switch (start[7]) {
										case 'b': switch (start[8]) {
											case 'e': switch (start[9]) {
												case 'l': return MLWORD_aria_label;
											}
										}
									}
								}
								case 'o': switch (start[6]) {
									case 'w': switch (start[7]) {
										case 'n': switch (start[8]) {
											case 'e': switch (start[9]) {
												case 'r': return MLWORD_aria_owner;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			case 'b': case 'B': switch (start[1]) {
				case 'l': case 'L': switch (start[2]) {
					case 'o': case 'O': switch (start[3]) {
						case 'c': case 'C': switch (start[4]) {
							case 'k': case 'K': switch (start[5]) {
								case 'q': case 'Q': switch (start[6]) {
									case 'u': case 'U': switch (start[7]) {
										case 'o': case 'O': switch (start[8]) {
											case 't': case 'T': switch (start[9]) {
												case 'e': case 'E': return MLWORD_blockquote;
											}
										}
									}
								}
							}
						}
					}
				}
				case 'a': case 'A': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'k': case 'K': switch (start[4]) {
							case 'g': case 'G': switch (start[5]) {
								case 'r': case 'R': switch (start[6]) {
									case 'o': case 'O': switch (start[7]) {
										case 'u': case 'U': switch (start[8]) {
											case 'n': case 'N': switch (start[9]) {
												case 'd': case 'D': return MLWORD_background;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			case 'h': case 'H': switch (start[1]) {
				case 't': case 'T': switch (start[2]) {
					case 't': case 'T': switch (start[3]) {
						case 'p': case 'P': switch (start[4]) {
							case '-': switch (start[5]) {
								case 'e': case 'E': switch (start[6]) {
									case 'q': case 'Q': switch (start[7]) {
										case 'u': case 'U': switch (start[8]) {
											case 'i': case 'I': switch (start[9]) {
												case 'v': case 'V': return MLWORD_http_equiv;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			case 'o': case 'O': switch (start[1]) {
				case 'n': case 'N': switch (start[2]) {
					case 'd': case 'D': switch (start[3]) {
						case 'b': case 'B': switch (start[4]) {
							case 'l': case 'L': switch (start[5]) {
								case 'c': case 'C': switch (start[6]) {
									case 'l': case 'L': switch (start[7]) {
										case 'i': case 'I': switch (start[8]) {
											case 'c': case 'C': switch (start[9]) {
												case 'k': case 'K': return MLWORD_ondblclick;
											}
										}
									}
								}
							}
						}
					}
					case 'k': case 'K': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'y': case 'Y': switch (start[5]) {
								case 'p': case 'P': switch (start[6]) {
									case 'r': case 'R': switch (start[7]) {
										case 'e': case 'E': switch (start[8]) {
											case 's': case 'S': switch (start[9]) {
												case 's': case 'S': return MLWORD_onkeypress;
											}
										}
									}
								}
							}
						}
					}
					case 'm': case 'M': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 'u': case 'U': switch (start[5]) {
								case 's': case 'S': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 'o': case 'O': switch (start[8]) {
											case 'u': case 'U': switch (start[9]) {
												case 't': case 'T': return MLWORD_onmouseout;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			case 's': switch (start[1]) {
				case 'p': switch (start[2]) {
					case 'e': switch (start[3]) {
						case 'l': switch (start[4]) {
							case 'l': switch (start[5]) {
								case 'c': switch (start[6]) {
									case 'h': switch (start[7]) {
										case 'e': switch (start[8]) {
											case 'c': switch (start[9]) {
												case 'k': return MLWORD_spellcheck;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		case 11: switch (start[0]) {
			case 'c': case 'C': switch (start[1]) {
				case 'e': case 'E': switch (start[2]) {
					case 'l': case 'L': switch (start[3]) {
						case 'l': case 'L': switch (start[4]) {
							case 'p': case 'P': switch (start[5]) {
								case 'a': case 'A': switch (start[6]) {
									case 'd': case 'D': switch (start[7]) {
										case 'd': case 'D': switch (start[8]) {
											case 'i': case 'I': switch (start[9]) {
												case 'n': case 'N': switch (start[10]) {
													case 'g': case 'G': return MLWORD_cellpadding;
												}
											}
										}
									}
								}
							}
							case 's': case 'S': switch (start[5]) {
								case 'p': case 'P': switch (start[6]) {
									case 'a': case 'A': switch (start[7]) {
										case 'c': case 'C': switch (start[8]) {
											case 'i': case 'I': switch (start[9]) {
												case 'n': case 'N': switch (start[10]) {
													case 'g': case 'G': return MLWORD_cellspacing;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			case 'f': case 'F': switch (start[1]) {
				case 'r': case 'R': switch (start[2]) {
					case 'a': case 'A': switch (start[3]) {
						case 'm': case 'M': switch (start[4]) {
							case 'e': case 'E': switch (start[5]) {
								case 'b': case 'B': switch (start[6]) {
									case 'o': case 'O': switch (start[7]) {
										case 'r': case 'R': switch (start[8]) {
											case 'd': case 'D': switch (start[9]) {
												case 'e': case 'E': switch (start[10]) {
													case 'r': case 'R': return MLWORD_frameborder;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			case 'm': case 'M': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 'g': case 'G': switch (start[4]) {
							case 'i': case 'I': switch (start[5]) {
								case 'n': case 'N': switch (start[6]) {
									case 'w': case 'W': switch (start[7]) {
										case 'i': case 'I': switch (start[8]) {
											case 'd': case 'D': switch (start[9]) {
												case 't': case 'T': switch (start[10]) {
													case 'h': case 'H': return MLWORD_marginwidth;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			case 'o': case 'O': switch (start[1]) {
				case 'n': case 'N': switch (start[2]) {
					case 'm': case 'M': switch (start[3]) {
						case 'o': case 'O': switch (start[4]) {
							case 'u': case 'U': switch (start[5]) {
								case 's': case 'S': switch (start[6]) {
									case 'e': case 'E': switch (start[7]) {
										case 'd': case 'D': switch (start[8]) {
											case 'o': case 'O': switch (start[9]) {
												case 'w': case 'W': switch (start[10]) {
													case 'n': case 'N': return MLWORD_onmousedown;
												}
											}
										}
										case 'm': case 'M': switch (start[8]) {
											case 'o': case 'O': switch (start[9]) {
												case 'v': case 'V': switch (start[10]) {
													case 'e': case 'E': return MLWORD_onmousemove;
												}
											}
										}
										case 'o': case 'O': switch (start[8]) {
											case 'v': case 'V': switch (start[9]) {
												case 'e': case 'E': switch (start[10]) {
													case 'r': case 'R': return MLWORD_onmousemove;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		case 12: switch (start[0]) {
			case 'm': case 'M': switch (start[1]) {
				case 'a': case 'A': switch (start[2]) {
					case 'r': case 'R': switch (start[3]) {
						case 'g': case 'G': switch (start[4]) {
							case 'i': case 'I': switch (start[5]) {
								case 'n': case 'N': switch (start[6]) {
									case 'h': case 'H': switch (start[7]) {
										case 'e': case 'E': switch (start[8]) {
											case 'i': case 'I': switch (start[9]) {
												case 'g': case 'G': switch (start[10]) {
													case 'h': case 'H': switch (start[11]) {
														case 't': case 'T': return MLWORD_marginheight;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		
		case 13: switch (start[0]) {
			case 'a': switch (start[1]) {
				case 'r': switch (start[2]) {
					case 'i': switch (start[3]) {
						case 'a': switch (start[4]) {
							case '-': switch (start[5]) {
								case 'h': switch (start[6]) {
									case 'a': switch (start[7]) {
										case 's': switch (start[8]) {
											case 'p': switch (start[9]) {
												case 'o': switch (start[10]) {
													case 'p': switch (start[11]) {
														case 'u': switch (start[12]) {
															case 'p': return MLWORD_aria_haspopup;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		case 14: switch (start[0]) {
			case 'a': case 'A': switch (start[1]) {
				case 'c': case 'C': switch (start[2]) {
					case 'c': case 'C': switch (start[3]) {
						case 'e': case 'E': switch (start[4]) {
							case 'p': case 'P': switch (start[5]) {
								case 't': case 'T': switch (start[6]) {
									case '-': switch (start[7]) {
										case 'c': case 'C': switch (start[8]) {
											case 'h': case 'H': switch (start[9]) {
												case 'a': case 'A': switch (start[10]) {
													case 'r': case 'R': switch (start[11]) {
														case 's': case 'S': switch (start[12]) {
															case 'e': case 'E': switch (start[13]) {
																case 't': case 'T': return MLWORD_accept_charset;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

	}

	return MLWORD_UNKNOWN;
}

