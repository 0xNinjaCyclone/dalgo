/*
    Huffman Compression Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 14-2-2024
    Compile     => gcc -I../DS/ -I../Algo/ ../Algo/helpers.c ../DS/heap.c ../DS/llist.c ../DS/hash.c ../Algo/huffman.c huffman_encode.c -o huffman_encode
*/

#include "huffman.h"

unsigned char *readfile(char *cpFileName, size_t *ulpFileSize)
{
    FILE *fp;
    unsigned char *pBuffer;

    if ( !(fp = fopen(cpFileName, "rb")) )
        return NULL;

    fseek(fp, 0L, SEEK_END);
    *ulpFileSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    if ( pBuffer = malloc(*ulpFileSize) )
        fread(pBuffer, *ulpFileSize, 1, fp);

    fclose(fp);
    return pBuffer;
}

bool writefile(char *cpFileName, unsigned char *pBuffer, size_t ulSize)
{
    FILE *fp;

    if ( !(fp = fopen(cpFileName, "wb")) )
        return false;

    fwrite(pBuffer, ulSize, 1, fp);
    fclose(fp);
    return true;
}

int main(int argc, char *argv[])
{
    unsigned char *pBuffer, *pEncodedData;
    size_t ulSize;
    bool bWritten;

    if ( argc <= 2 )
        return puts("Usage :\n\t./huffman_encode <original.txt> <encoded.bin>");

    if ( !(pBuffer = readfile(argv[1], &ulSize)) )
        return puts("[!] Failed to read the input file");

    printf("[*] Original data size   => %dB ( %dKB )\n", ulSize, ulSize/1024);
    pEncodedData = huffman_encode(pBuffer, ulSize, false, &ulSize);
    free( pBuffer );

    if ( ! pEncodedData )
        return puts("[!] Failed to compress the given file data");

    printf("[*] Compressed data size => %dB ( %dKB )\n", ulSize, ulSize/1024);
    bWritten = writefile(argv[2], pEncodedData, ulSize);
    free( pEncodedData );

    if ( ! bWritten )
        return puts("[!] Failed to write the output into the file");

    printf("[+] The data successfully compressed and has been written to '%s'\n", argv[2]);
    return 0;
}