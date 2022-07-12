/**
 @file
 sy.write.c
 
 @name 
 sy.write
 
 @realname 
 sy.write
 
 @type
 object
 
 @module
 sy
 
 @author
 Daniele Ghisi
 
 @digest 
 Write text to file
 
 @description
 Saves text to a file on disk
 
 @discussion
 
 @category
 sy
 
 @keywords
 save, write, symbol, file
 
 @seealso
 sy.read
 
 @owner
 Daniele Ghisi
 */


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _write 
{
	t_sy_object		n_ob;		// the object itself (must be first)

    void			*n_proxy;
    long			n_in;

    void			*n_outlet;
} t_write;



///////////////////////// function pwriteotypes
//// standard set
void *write_new(t_symbol *s, long argc, t_atom *argv);
void write_free(t_write *x);
void write_assist(t_write *x, void *b, long m, long a, char *s);
void write_inletinfo(t_write *x, void *b, long a, char *t);

void write_int(t_write *x, t_atom_long num);
void write_float(t_write *x, double num);
void write_anything(t_write *x, t_symbol *msg, long ac, t_atom *av);
void write_write(t_write *x, t_symbol *s);


//////////////////////// global class pointer variable
void *write_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();
	
	c = class_new("sy.write", (method)write_new, (method)write_free, (long)sizeof(t_write), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)write_assist,			"assist",		A_CANT, 0);  
    class_addmethod(c, (method)write_inletinfo,	"inletinfo",	A_CANT,		0);

	// @method anything @digest Set text to be saved
	// @description Anything in the right inlet is consider as the text to be saved
	class_addmethod(c, (method)write_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)write_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)write_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)write_anything,		"anything",		A_GIMME,	0);

    // @method write @digest Save to disk
    // @description Saves the text to disk. The optional argument sets the filename
    // @marg 0 @name filename @optional 1 @type symbol
    class_addmethod(c, (method)write_write,			"write",       A_DEFSYM, 0);
	
    class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	write_class = c;
	
	return 0;
}


void write_assist(t_write *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
        if (a == 0) // @in 0 @type write @digest Write file to disk
            sprintf(s, "write");
        else // @in 1 @type anything @digest Incoming symbols
            sprintf(s, "anything: Incoming symbols");
	}
	else {	// @out 0 @type bang @digest bang when saving has ended
		sprintf(s, "bang When Finished Saving");
	}
}


void write_inletinfo(t_write *x, void *b, long a, char *t)
{
    if (a)
        *t = 1;
}

void write_free(t_write *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *write_new(t_symbol *s, long argc, t_atom *argv)
{
	t_write *x = NULL;
    
	if ((x = (t_write *)object_alloc(write_class))) {
				
        syobj_obj_setup((t_sy_object *)x, 2);

        attr_args_process(x, argc, argv);
		
        x->n_proxy = proxy_new((t_object *) x, 1, &x->n_in);

		x->n_outlet = bangout(x);
	}
	return (x);
}

void write_int(t_write *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	write_anything(x, _sym_list, 1, argv);
}

void write_float(t_write *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	write_anything(x, _sym_list, 1, argv);
}


t_max_err sy_openfile_write(t_symbol *filename_sym, const char *default_filename, t_filehandle *fh,
                              t_fourcc *types, long numtypes, t_fourcc *outtype, char *output_filename, short *output_path)
{
    char filename[MAX_PATH_CHARS];
    short path;
    long err;
    
    if (!filename_sym || filename_sym == gensym("")) {      // if no argument supplied, ask for file
        strncpy_zero(filename, default_filename, MAX_PATH_CHARS);
        if (saveasdialog_extended(filename, &path, outtype, types, numtypes)) {    // non-zero: user cancelled
            return MAX_ERR_GENERIC;
        }
        if (!strchr(filename, '.')) {
            const char *ext = strrchr(default_filename, '.');
            strncat_zero(filename, ext, MAX_PATH_CHARS);
        }
    } else {
        strncpy_zero(filename, filename_sym->s_name, MAX_PATH_CHARS);
        path = path_getdefault();
    }
    err = path_createsysfile(filename, path, 'TEXT', fh);
    sysfile_seteof(*fh, 0);
    
    if (filename && output_filename)
        strncpy_zero(output_filename, filename, MAX_PATH_CHARS);
    if (output_path)
        *output_path = path;
    
    return err;
}

t_max_err do_write_textfile(t_symbol *filename_sym, t_ptr_size *count, const void *buffer)
{
    long err;
    t_filehandle fh;
    t_fourcc outtype;
    t_fourcc filetype = 'TEXT';
    //bach_fix_filename_extension(&filename_sym, "txt");
    err = sy_openfile_write(filename_sym, "Untitled.txt", &fh, &filetype, 1, &outtype, NULL, NULL);
    if (err)
        return err;
    //	err = sysfile_writetextfile(fh, (t_handle) &buffer, TEXT_LB_MAC);
    err = sysfile_write(fh, count, buffer);
    //err = sysfile_seteof(fh, *count);
    sysfile_close(fh);
    return err;
}

void write_do_write(t_write *x, t_symbol *s, long ac, t_atom *av)
{
    t_symbol *filepath = atom_getsym(av);
    t_symbol *to_save = atom_getsym(av+1);
    t_ptr_size len = strlen(to_save->s_name);
    if (do_write_textfile(filepath, &len, to_save->s_name))
        object_error((t_object *)x, "Error writing to file.");
    outlet_bang(x->n_outlet);
}

void write_write(t_write *x, t_symbol *s)
{
    t_atom av[2];
    t_symbol *to_save = syobj_get_store_contents_as_single_symbol((t_sy_object *)x, 1);
    atom_setsym(av, s);
    atom_setsym(av+1, to_save);
    defer(x, (method)write_do_write, NULL, 2, av);
}

void write_anything(t_write *x, t_symbol *msg, long ac, t_atom *av)
{
    long inlet = proxy_getinlet((t_object *) x);

	if (msg != _sym_bang && inlet == 1)
		syobj_store_content((t_sy_object *) x, msg, ac, av, 1);
}
