/* mask for high order 4 bits of byte */
#define CAT_HIGH_NIBBLE 0xf0
#define CAT_MAX_BYTE 0xff

#define CAT_ESCAPE_CODE 0x80
#define CAT_ESCAPE_MASK 0x7f
#define CAT_MAX_ESCAPE 0x7f
/* nonzero if escape command and zero otherwise */
#define CAT_IS_ESCAPE(x) (((x) & (CAT_HIGH_NIBBLE << 3)) == CAT_ESCAPE_CODE)
/* magnitude of escape */
#define CAT_ESCAPE(x) (~(x) & CAT_ESCAPE_MASK)
#define CAT_ENCODE_ESCAPE(n) (CAT_ESCAPE_CODE | (~(n) & CAT_ESCAPE_MASK))

#define CAT_LEAD_CODE 0x60
#define CAT_LEAD_MASK 0x1f
#define CAT_MAX_LEAD 0x1f
/* nonzero if leading command and zero otherwise */
#define CAT_IS_LEADING(x) (((x) & (CAT_HIGH_NIBBLE << 1)) == CAT_LEAD_CODE)
/* magnitude of leading */
#define CAT_LEAD(x) (~(x) & CAT_MAX_LEAD)
#define CAT_ENCODE_LEAD(n) (CAT_LEAD_CODE | (~(n) & CAT_LEAD_MASK))

#define CAT_SIZE_CHANGE_CODE 0x50
/* nonzero if point size change command and zero otherwise */
#define CAT_IS_SIZE_CHANGE(x) (((x) & CAT_HIGH_NIBBLE) == CAT_SIZE_CHANGE_CODE)

/* translates from the weird CAT point size change codes into something sane */
#define CAT_SIZE_CHANGE(x) \
	((x) == 0x50 ? 7 : \
	 (x) == 0x51 ? 8 : \
	 (x) == 0x52 ? 10 : \
	 (x) == 0x53 ? 11 : \
	 (x) == 0x54 ? 12 : \
	 (x) == 0x55 ? 14 : \
	 (x) == 0x56 ? 18 : \
	 (x) == 0x57 ? 9 : \
	 (x) == 0x58 ? 6 : \
	 (x) == 0x59 ? 16 : \
	 (x) == 0x5a ? 20 : \
	 (x) == 0x5b ? 22 : \
	 (x) == 0x5c ? 24 : \
	 (x) == 0x5d ? 28 : \
	 (x) == 0x5e ? 36 : 0)

/* translates from sane point sizes into the weird CAT encodings */
#define CAT_ENCODE_SIZE(x) \
	((x) == 6 ? 0x58 : \
	 (x) == 7 ? 0x50 : \
	 (x) == 8 ? 0x51 : \
	 (x) == 9 ? 0x57 : \
	 (x) == 10 ? 0x52 : \
	 (x) == 11 ? 0x53 : \
	 (x) == 12 ? 0x54 : \
	 (x) == 14 ? 0x55 : \
	 (x) == 16 ? 0x59 : \
	 (x) == 18 ? 0x56 : \
	 (x) == 20 ? 0x5a : \
	 (x) == 22 ? 0x5b : \
	 (x) == 24 ? 0x5c : \
	 (x) == 28 ? 0x5d : \
	 (x) == 36 ? 0x5e : 0)

#define CAT_FLASH_CODE 0x00
#define CAT_FLASH_MASK 0x3f
#define CAT_MAX_FLASH 0x3f
/* nonzero if printable character and zero otherwise */
#define CAT_IS_FLASH(x) (((x) & (CAT_HIGH_NIBBLE << 2)) == CAT_FLASH_CODE)
#define CAT_FLASH(x) ((x) & CAT_MAX_FLASH)
#define CAT_ENCODE_FLASH(n) (CAT_FLASH_CODE | ((n) & CAT_FLASH_MASK))

#define CAT_CONTROL_CODE 0x40
/* nonzero if control command and zero otherwise */
#define CAT_IS_CONTROL(x) (((x) & CAT_HIGH_NIBBLE) == CAT_CONTROL_CODE)

/* CAT-8 control commands */
#define CAT_INITIALIZE 0x40
#define CAT_LOWER_RAIL 0x41
#define CAT_UPPER_RAIL 0x42
#define CAT_UPPER_MAGAZINE 0x43
#define CAT_LOWER_MAGAZINE 0x44
#define CAT_LOWER_FONT 0x45
#define CAT_UPPER_FONT 0x46
#define CAT_ESCAPE_FORWARD 0x47
#define CAT_ESCAPE_BACKWARD 0x48
#define CAT_STOP 0x49
#define CAT_LEAD_FORWARD 0x4a
#define CAT_LEAD_BACKWARD 0x4c
#define CAT_TILT_UP 0x4e
#define CAT_TILT_DOWN 0x4f
#define CAT_NOOP 0x00
/* trapdoor for CAT extensions */
#define CAT_EXTENSION 0x4b

/* CAT_BIG_LEAD means take the next byte * 64 to obtain leading */
#define CAT_BIG_LEAD 0x01
#define CAT_BIG_LEAD_MULTIPLIER 64
#define CAT_MIN_BIG_LEAD (CAT_BIG_LEAD_MULTIPLIER * 0x01)
#define CAT_MAX_BIG_LEAD (CAT_BIG_LEAD_MULTIPLIER * 0xff)

/* CAT_BIG_ESCAPE means take the next byte * 128 to obtain escape */
#define CAT_BIG_ESCAPE 0x02
#define CAT_BIG_ESCAPE_MULTIPLIER 128
#define CAT_MIN_BIG_ESCAPE (CAT_BIG_ESCAPE_MULTIPLIER * 0x01)
#define CAT_MAX_BIG_ESCAPE (CAT_BIG_ESCAPE_MULTIPLIER * 0xff)

/*
 * CAT_FORMFEED means advance to next page resetting current row
 * and column to <0,0>.
 */
#define CAT_FORMFEED 0x03

/*
 * Returns nonzero if a single point size and zero otherwise.
 * The parameter is the `sane' point size and NOT the weird CAT encoding.
 */
#define CAT_IS_SINGLE(p) ((6 <= (p) && (p) <= 14) || (p) == 18)

/*
 * Returns nonzero is a double point size and zero otherwise.
 * The parmeter is the `sane' point size and NOT the weird CAT encoding.
 */
#define CAT_IS_DOUBLE(p) ((p) == 16 || (p) >= 20)

/*
 * Returns nonzero if the old to new point size transition is a
 * single to double transition and zero otherwise.
 * The parameters are the `sane' point sizes NOT the weird CAT encodings.
 */
#define CAT_IS_SINGLE_TO_DOUBLE(old, new) \
	(CAT_IS_SINGLE(old) && CAT_IS_DOUBLE(new))

/*
 * Returns nonzero if the old to new point size transition is a
 * double to single transition and zero otherwise.
 * The parameters are the `sane' point sizes NOT the weird CAT encodings.
 */
#define CAT_IS_DOUBLE_TO_SINGLE(old, new) \
	(CAT_IS_DOUBLE(old) && CAT_IS_SINGLE(new))

typedef struct CAT {
	char escape_where;	/* BACKWARD or FORWARD */
	char lead_where;	/* BACKWARD or FORWARD */
	char font;		/* bit 0 => tilt, bit 1 => rail, bit 2 => magazine */
	char font_half;		/* LOWER or UPPER */
	char point_size;	/* current point size */
} CAT;

#define CAT_FORWARD 0
#define CAT_BACKWARD 1
#define CAT_UPPER 0
#define CAT_LOWER 1

/* vertical resolution per inch */
#define CAT_VERTICAL_UNITS 144.0
/* horizontal resolution per inch */
#define CAT_HORIZONTAL_UNITS 432.0

/* compensatory escape for single/double point size transitions */
#define CAT_LENSE_COMPENSATION 55

#define CAT_TILT 01
#define CAT_RAIL 02
#define CAT_MAGAZINE 04

/* default troff and scribe font mountings for CAT-8 */
#define CAT_ROMAN_FONT 0
#define CAT_ITALIC_FONT 2
#define CAT_BOLD_FONT 4
#define CAT_SPECIAL_FONT 6

/* the maximum number of characters on a filmstrip */
#define CAT_MAX_FONT_INDEX 108
