/*
    Non-Binary Tree Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 25-07-2024
    Compile     => gcc -I../DS/ -I../Algo/ ../Algo/helpers.c ../DS/llist.c ../DS/tree.c tree.c -o tree
    Note        => Use '-DUSE_DALGO_STRUCTURES' to allow the tree to use the dalgo data structures
*/

#include "tree.h"
#include "helpers.h"
#include <dirent.h>
#include <sys/stat.h>
#include <libgen.h>


void build_filesystem_tree(Tree *pTree, TreeNode *pParent, char *cpPath)
{
    TreeNode *pChild;
    DIR *pDir;
    struct dirent *pDirent;
    struct stat st;
    char *cpParentName, *cpChildName;
    char cChildPath[FILENAME_MAX] = { 0 };

    if ( pDir = opendir(cpPath) )
    {
        cpParentName = strdup( basename(cpPath) );
        pChild = tree_insert(pTree, pParent, &cpParentName);

        while ( pDirent = readdir(pDir) )
        {
            if ( strcmp(pDirent->d_name, ".") != 0 && strcmp(pDirent->d_name, "..") != 0 )
            {                
                strcpy( cChildPath, cpPath );
                if ( cpPath[strlen(cpPath) - 1] != '/' )
                    strcat( cChildPath, "/" );
                strcat( cChildPath, pDirent->d_name );
                stat( cChildPath, &st );

                if ( S_ISDIR(st.st_mode) ) { 
                    build_filesystem_tree( pTree, pChild, cChildPath );
                }

                else {
                    cpChildName = strdup( pDirent->d_name );
                    tree_insert( pTree, pChild, &cpChildName );
                }

            }
        }

        closedir( pDir );
    }
}

void custom_free(void *ptr)
{
    free( *(void **)ptr );
    free( ptr );
}

int main(int argc, char **argv)
{
    Tree *pTree;
    TreeNode *pGitTreeBranch;
    char cDirName[] = ".git";

    if ( argc < 2 )
        return puts("Usage :\n\t./tree <path/to/>");

    pTree = tree_init(sizeof(char *), malloc, custom_free, StrPtrPrintA, StrPtrCmpA);

    if ( pTree ) {
        build_filesystem_tree( pTree, NULL, argv[1] );
        tree_print( pTree );
        printf("[+] Number of Nodes -> %lu\n", pTree->ulSize);
        if ( pGitTreeBranch = tree_find(pTree, NULL, &cDirName) ) {
            printf("[+] Git branch data -> '%s'\n", *(char **)pGitTreeBranch->data);
            printf("[+] Number of Child -> %d\n", treenode_numofchild(pGitTreeBranch));
            puts("------");
            tree_print2( pTree, pGitTreeBranch );
            puts("------");
        } else {
            printf("[!] Cannot find '%s'\n", cDirName);
        }
        tree_cleanup( &pTree );
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}