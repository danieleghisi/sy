/**
 @file
 sy.read.c
 
 @name 
 sy.read
 
 @realname 
 sy.read
 
 @type
 object
 
 @module
 sy
 
 @author
 Daniele Ghisi
 
 @digest 
 Read text file
 
 @description
 Opens a text file from disk
 
 @discussion
 
 @category
 sy
 
 @keywords
 read, open, file, symbol
 
 @seealso
 sy.read
 
 @owner
 Daniele Ghisi
 */

#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _read
{
    t_sy_object		n_ob;		// the object itself (must be first)
    
    long            auto_output;

    void			*n_outlet1;
    void			*n_outlet2;
} t_read;



///////////////////////// function preadotypes
//// standard set
void *read_new(t_symbol *s, long argc, t_atom *argv);
void read_free(t_read *x);
void read_assist(t_read *x, void *b, long m, long a, char *s);
void read_inletinfo(t_read *x, void *b, long a, char *t);

void read_read(t_read *x, t_symbol *s);

void read_bang(t_read *x);

//////////////////////// global class pointer variable
void *read_class;


int C74_EXPORT main(void)
{
    // object initialization, NEW STYLE
    t_class *c;
    
    common_symbols_init();
    
    c = class_new("sy.read", (method)read_new, (method)read_free, (long)sizeof(t_read),
                  0L /* leave NULL!! */, A_GIMME, 0);
    
    /* you CAN'T call this from the patcher */
    class_addmethod(c, (method)read_assist,			"assist",		A_CANT, 0);
    class_addmethod(c, (method)read_inletinfo,	"inletinfo",	A_CANT,		0);
    
    // @method read @digest Load from disk
    // @description Opens a text file from disk. The optional argument sets the filename.
    // @marg 0 @name filename @optional 1 @type symbol
    class_addmethod(c, (method)read_read,			"read",       A_DEFSYM, 0);

    // @method bang @digest Output text
    // @description Outputs the loaded text
    class_addmethod(c, (method)read_bang,			"bang", 0);

    syobj_class_add_listout_attr(c);

    CLASS_ATTR_LONG(c, "auto", 0, t_read, auto_output);
    CLASS_ATTR_STYLE_LABEL(c,"auto",0,"onoff","Automatically Output Text");
    CLASS_ATTR_BASIC(c,"auto",0);
    // @description Toggles the ability to automatically output the text when loaded

    
    class_register(CLASS_BOX, c); /* CLASS_NOBOX */
    read_class = c;
    
    return 0;
}


void read_assist(t_read *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) {
        // @in 0 @type read @digest Read file from disk
        sprintf(s, "read/bang");
    }
    else {
        if (a == 0) // @out 0 @type anything @digest Loaded text
            sprintf(s, "anything: Loaded text");
        else // @out 1 @type bang @digest bang when saving has ended
            sprintf(s, "bang When Finished Reading");
    }
}


void read_inletinfo(t_read *x, void *b, long a, char *t)
{
    if (a)
        *t = 1;
}

void read_free(t_read *x)
{
    syobj_obj_free((t_sy_object *)x);
}


void *read_new(t_symbol *s, long argc, t_atom *argv)
{
    t_read *x = NULL;
    
    if ((x = (t_read *)object_alloc(read_class))) {
        
        x->auto_output = true;
        
        syobj_obj_setup((t_sy_object *)x, 1);
        
        attr_args_process(x, argc, argv);
        
        x->n_outlet2 = bangout(x);
        x->n_outlet1 = syout((t_object *)x);
    }
    return (x);
}



t_max_err sy_openfile_for_read(t_object *x, t_symbol *filename_sym, short *path, t_fourcc *types, long numtypes, t_fourcc *outtype, char *filename)
{
    if (!filename_sym || filename_sym == gensym("")) {      // if no argument supplied, ask for file
        if (open_dialog(filename, path, outtype, types, numtypes)) {     // non-zero: user cancelled
            *filename = 0;
            return MAX_ERR_NONE;
        }
    } else {
        strcpy(filename, filename_sym->s_name);    // must copy symbol before calling locatefile_extended
        if (locatefile_extended(filename, path, outtype, types, numtypes)) { // non-zero: not found
            *filename = 0;
            object_error(x, "%s: not found", filename_sym->s_name);
            return MAX_ERR_GENERIC;
        }
    }
    return MAX_ERR_NONE;
}

t_max_err sy_get_file_handle(t_object *x, const char *filename, short path, t_filehandle *fh)
{
    if (path_opensysfile(filename, path, fh, READ_PERM)) {
        object_error(x, "Error opening %s", filename);
        return MAX_ERR_GENERIC;
    }
    return MAX_ERR_NONE;
}

char *sy_readfile(t_object *x, t_filehandle fh)
{
    t_ptr_size size;
    char *buffer;
    
    // allocate memory block that is the size of the file
    sysfile_geteof(fh, &size);
    buffer = (char *) sysmem_newptr((size + 1) * sizeof(char));
    
    // read in the file
    sysfile_read(fh, &size, buffer);
    buffer[size] = 0;
    sysfile_close(fh);
    
    return buffer;
}



t_max_err do_read_textfile(t_object *x, t_symbol *filename_sym, char **outbuf)
{
    t_fourcc outtype = 0;
    t_fourcc filetype[] = {'TEXT'};
    t_filehandle fh;
    short path;
    char filename[MAX_PATH_CHARS];
    
    if (sy_openfile_for_read(x, filename_sym, &path, filetype, sizeof(filetype) / sizeof(t_fourcc), &outtype, filename) != MAX_ERR_NONE // file not found
        || *filename == 0) // canceled by user
        return MAX_ERR_NONE;
    
    if (sy_get_file_handle(x, filename, path, &fh) != MAX_ERR_NONE) {
        object_error((t_object *)x, "Error while reading file.");
        return MAX_ERR_GENERIC;
    }
    *outbuf = sy_readfile(x, fh);
    
    return MAX_ERR_NONE;
}

void read_do_read(t_read *x, t_symbol *s, long ac, t_atom *av)
{
    t_symbol *filepath = atom_getsym(av);
    char *outbuf = NULL;
    if (do_read_textfile((t_object *)x, filepath, &outbuf))
        object_error((t_object *)x, "Error writing to file.");
    
    if (outbuf) {
        long out_ac = 1;
        t_atom *out_av = (t_atom *)sysmem_newptr(sizeof(t_atom));
        
        atom_setsym(out_av, gensym(outbuf));
        // THIS IS A PROBLEM WITH FILES MORE THAN 32k!
        // Indeed Max has as maximum symbol length 32767...
        
        syobj_store_content((t_sy_object *)x, NULL, out_ac, out_av, 0);
        
        outlet_bang(x->n_outlet2);
        if (x->auto_output) { // also output immediately
            syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
            sy_outlet(x->n_outlet1, NULL, out_ac, out_av);
        }
        
        sysmem_freeptr(outbuf);
    }
}


void read_bang(t_read *x)
{
    t_atom *out_av;
    long out_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE, &out_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
    sy_outlet(x->n_outlet1, NULL, out_ac, out_av);
}

void read_read(t_read *x, t_symbol *s)
{
    t_atom av[1];
    atom_setsym(av, s);
    defer(x, (method)read_do_read, NULL, 1, av);
}
