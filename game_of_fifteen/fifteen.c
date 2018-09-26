/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// "blank" coordinates
int rt=0;
int ct=0;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    rt=d-1;
    ct=d-1;
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    //POPULATE BOARD
    int num = d*d-1; //decrementing variable that represents the numbers on the board 
    for(int r=0; r<d; r++) //populate board
    {
        for(int c=0; c<d; c++)
        {
            board[r][c] = num;
            num--; 
        }
    }

    //*IF DIMENSIONS ARE EVEN*, SWAP '1' & '2' 
    if(d%2==0)
    {
        for(int i=0; i<d; i++)
        {
            if(board[d-1][i]==2) 
            {
                //find '2' and swap with '1' (subsequent index)
                board[d-1][i]=1; //targets are always on (d-1)th/bottom row
                board[d-1][i+1]=2;
                break;
            }
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    printf("\n\n\n");
    // PRINT BOARD ROW BY ROW
    for(int r=0; r<d; r++) 
    {
        bool blank=false;
        for(int c=0; c<d; c++)
        {
            
            if(r==rt && c==ct)
            {
                printf("   _  "); //print blank tile
                blank=true;
            }
            if(blank==false)
            {
                 printf("  %2i  ", board[r][c]);
            }
            blank = false;
        }
        printf("\n\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    //DETERMINE LOCATION OF TILE
    //iterate through board row-by-row
    for(int r=0; r<d; r++)
    {
        for(int c=0; c<d; c++)
        {
            if(board[r][c]==tile) //position of tile found
            {
                //DETERMINE LEGAILITY OF MOVE by comparing tile-pos with blank-pos
                if(r==rt) //target on same row as blank 
                {
                    if(c+1==ct)//target on left of blank PROBLEM
                    {
                        //TILE SWAP
                        board[rt][c+1]=tile; //re-position tile
                        ct=c; //re-position blank
                        return true;
                    }
                    else if(c-1==ct)//target on right of tile
                    {
                        //TILE SWAP
                        board[rt][ct]=tile;
                        ct=c;
                        return true;
                    }
                }
                else if(r-1==rt)//target above blank
                {
                    if(c==ct)
                    {
                        board[rt][ct]=tile;
                        rt++;
                        return true;
                    }
                }
                else if(r+1==rt)//target below blank
                {
                    if(c==ct)
                    {
                        board[rt][ct]=tile;
                        rt--;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    //CHECK IF BOARD IS IN ASCENDING ORDER
    int num = 1;
    for(int r=0; r<d; r++) //iterate through and verify tiles one-by-one
    {
        for(int c=0; c<d; c++)
        {
            if(board[r][c] != num && r != (d-1) && c != (d-1))
            {
                return false; //misplaced tile
            }
            num++;
        }
    }
    
    //CHECK IF BLANK IS IN "WON POSITION
    if(rt==(d-1)&&ct==(d-1))
    {
        return true;
    }
    return false;
}