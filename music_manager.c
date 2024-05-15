/** @file music_manager.c
 *  @brief A small program to analyze songs data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Victoria L.
 *  @author Lee Napthine
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LINE_LEN 256

/**
 * @brief Displays the content of the "output.csv" file on the console.
 *
 * @return void
 */
void displayOutput() {

    char line[MAX_LINE_LEN];
    FILE *file = fopen("output.csv", "r");

    if (file == NULL) {
        printf("Output file not available.\n");
        return; }

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line); }

    fclose(file); }

/**
 * @brief Prints the content of a node to the "output.csv" file.
 *
 * @param p The pointer to the node to print.
 * @param arg The format string.
 * @param sortBy The criteria variable used to sort the list.
 * @param display The remaining number of nodes to display.
 * @return void
 */
void printNode(node_t *p, void *arg, char *sortBy, int *display) {
    
    Song *song = p->song;
    FILE *file = fopen("output.csv", "a"); 

        if (file == NULL) {
            printf("file error\n");
            return; }

        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            fprintf(file, "artist,song,year");

        if (strcmp(sortBy, "energy") == 0) {
            fprintf(file, ",energy\n"); } 
        else if (strcmp(sortBy, "popularity") == 0) {
            fprintf(file, ",popularity\n"); } 
        else if (strcmp(sortBy, "danceability") == 0) {
            fprintf(file, ",danceability\n"); } }

        if (*display > 0) {
            if (strcmp(sortBy, "energy") == 0) {
                fprintf(file, "%s,%s,%d,%.3g\n", song->artist, song->title, song->year, song->energy); } 
            else if (strcmp(sortBy, "popularity") == 0) {
                fprintf(file, "%s,%s,%d,%d\n", song->artist, song->title, song->year, song->popularity); } 
            else if (strcmp(sortBy, "danceability") == 0) {
                fprintf(file, "%s,%s,%d,%.3g\n", song->artist, song->title, song->year, song->danceability); } 
            (*display)--; }

        fclose(file); }

/**
 * @brief Prints each node in the list to the "output.csv" file.
 *
 * @param l The first node in the list.
 * @param sortBy The criteria variable used to sort the list.
 * @param display The number of nodes to display.
 * @return void
 */
void analysis(node_t *l, char *sortBy, int *display) {

    FILE *file = fopen("output.csv", "w");
    fclose(file);
    apply(l, printNode, "%s\n", sortBy, display); }

/**
 * @brief Adds a new song to the list.
 *
 * @param newSong The pointer to the new song.
 * @param songList The pointer to the pointer of the song list.
 * @param sortBy The criteria variable used to sort the list.
 * @return void
 */
void addToList(Song *newSong, node_t **songList, char *sortBy) {

    node_t *songNode = new_node(newSong);
    node_t *updatedList = add_inorder(*songList, songNode, sortBy);
    *songList = updatedList; }

/**
 * @brief Reads the file specified in the ParsedArgs structure and creates a song list.
 *
 * @param arg The pointer to the ParsedArgs structure.
 * @return node_t* The pointer to the first node of the created song list.
 */
node_t* readFile(ParsedArgs *arg) {
    
    FILE *file = fopen(arg->file, "r");
    node_t *songList = NULL;
    char line[MAX_LINE_LEN];
    fgets(line, sizeof(line), file);

    if (file == NULL) {
        printf("file not avail.\n");
        return NULL; } 

    while (fgets(line, sizeof(line), file) != NULL) {

        Song* newSong = (Song*)malloc(sizeof(Song));
        newSong->artist = (char*)malloc(100 * sizeof(char));
        newSong->title = (char*)malloc(100 * sizeof(char));

        sscanf(line, "%[^,],%[^,],%*[^,],%*[^,],%d,%d,%f,%f", newSong->artist, newSong->title, 
        &(newSong->year), &(newSong->popularity), &(newSong->danceability), &(newSong->energy));

        addToList(newSong, &songList, arg->sortBy); }

    fclose(file);
    return songList; }

/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0 if no errors occurred; 1 if errors were produced.
 */
int main(int argc, char *argv[]) { 
    char *line = NULL;
    char *t;
    ParsedArgs args; 
    line = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
    for (int i = 1; i < argc; i++) {
        strcpy(line, argv[i]);
        line[strcspn(line, "\n")] = '\0';
        t = strtok(line, "=");

        while (t) {
            if (strcmp(t, "--sortBy") == 0) {
                t = strtok(NULL, "=");
                if (t != NULL)
                    strncpy(args.sortBy, t, sizeof(args.sortBy) - 1); }

            if (strcmp(t, "--display") == 0) {
                t = strtok(NULL, "=");
                if (t != NULL)
                    args.display = atoi(t); }

            if (strcmp(t, "--files") == 0) {
                t = strtok(NULL, "=");
                if (t != NULL)
                     strncpy(args.file, t, sizeof(args.file) - 1); }

            t = strtok(NULL, "="); } }

    node_t *songList = readFile(&args);
    analysis(songList, args.sortBy, &args.display);
    node_t *temp_n = NULL;

    for (; songList != NULL; songList = temp_n) {
        temp_n = songList->next;
        free(songList->song);
        free(songList); }
        
    free(line);
    displayOutput();

    exit(0); }
