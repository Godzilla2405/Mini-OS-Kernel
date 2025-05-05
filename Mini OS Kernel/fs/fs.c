// fs/fs.c

#include "../lib/string.c"
#include "../kernel/terminal.c"

#define MAX_FILES 8
#define MAX_FILENAME 16
#define MAX_FILESIZE 128

typedef struct
{
    char name[MAX_FILENAME];
    char content[MAX_FILESIZE];
    int used;
} File;

static File files[MAX_FILES];

void fs_init()
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        files[i].used = 0;
    }

    // Example files
    fs_create("readme.txt", "Welcome to Mini OS!");
    fs_create("info.txt", "This is a simple in-memory FS.");
}

int fs_create(const char *name, const char *content)
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (!files[i].used)
        {
            str_copy(files[i].name, name);
            str_copy(files[i].content, content);
            files[i].used = 1;
            return 1;
        }
    }
    return 0;
}

const char *fs_read(const char *name)
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (files[i].used && str_compare(files[i].name, name) == 0)
        {
            return files[i].content;
        }
    }
    return "File not found.\n";
}

void fs_list()
{
    terminal_writestring("Files:\n");
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (files[i].used)
        {
            terminal_writestring("- ");
            terminal_writestring(files[i].name);
            terminal_putchar('\n');
        }
    }
}
