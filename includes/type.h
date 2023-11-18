#ifndef TYPE_H
# define TYPE_H

enum e_exit_code
{
	EIXT_BUILTIN = 2,
	EXIT_EXEC = 126,
	EXIT_NOENT,
	EXIT_INVAL,
	EXIT_SEGV = 255
};

#endif