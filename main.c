#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BEAD(i, j) beads[i * max + j]

GLint osq[3][4] = {{0, 1, 1, 0}, {0, 0, 1, 1}, {1, 1, 1, 1}};
GLint nsq[3][4] = {{0, 1, 1, 0}, {0, 0, 1, 1}, {1, 1, 1, 1}};
GLint tsq[3][4] = {{0, 1, 1, 0}, {0, 0, 1, 1}, {1, 1, 1, 1}};
GLint scalem[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
GLint transm[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
GLint *a;
GLint n;
char type = 'r';
char order = 'a';
int font = 0;

static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 0;
clock_t start, finish;

void display();
void multiply(char);
void scale(int);
void translate(int);
void randomize();
void cube();
void drawtext(int, int, int, char *);
void bsort(int[], int);
void delay(int);
void quickSort(int[], int, int, int);
int partition(int[], int, int, int);
void msgtext(int, int, int, char *);
void swap(int *, int *);
void heapify(int[], int, int);

void heapifyd(int[], int, int);

void display()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (type)
    {
    case 'r':
        drawtext(0, n, 0, "Randomized");
        break;
    case 'q':
        drawtext(0, n, 0, "Quick Sort | Execution time in ms=");
        break;
    case 'b':
        drawtext(0, n, 0, "Bubble Sort | Execution time in ms=");
        break;
    case 'g':
        drawtext(0, n, 0, "Gravity Sort | Execution time in ms=");
        break;
    case 's':
        drawtext(0, n, 0, "Selection Sort | Execution time in ms=");
        break;
    case 'i':
        drawtext(0, n, 0, "Insertion Sort | Execution time in ms=");
        break;
    case 'h':
        drawtext(0, n, 0, "Heap Sort | Execution time in ms=");
        break;
    case 'm':
        drawtext(0, n, 0, "Merge Sort | Execution time in ms=");
        break;
    }
    for (i = 0; i < n; i++)
    {
        scale(a[i]);
        translate(i);
        nsq[0][0] = 0 + 2 * i;
        nsq[1][0] = 0;
        nsq[0][1] = 1 + 2 * i;
        nsq[1][1] = 0;
        cube();
    }
    glFlush();
    glutSwapBuffers();
}

void display1()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    char msg[50];
    font = 1;
    sprintf(msg, "%s", "BANGALORE INSTITUTE OF TECHNOLOGY");
    msgtext(3 * n / 4, 5 * n / 4, 0, msg);
    font = 2;
    sprintf(msg, "%s", "DEPARTMENT OF COMPUTER SCIENCE & ENGINEERING");
    msgtext(3 * n / 4, 23 * n / 20, 0, msg);
    font = 1;
    sprintf(msg, "%s", "AN OPENGL MINI PROJECT ON:");
    msgtext(83 * n / 100, 20 * n / 20, 0, msg);
    font = 2;
    sprintf(msg, "%s", "VISUALIZATION OF VARIOUS SORTING ALGORITHMS");
    msgtext(76 * n / 100, 9 * n / 10, 0, msg);
    font = 3;
    sprintf(msg, "%s", "<Press enter to continue>");
    msgtext(92 * n / 100, 5 * n / 10, 0, msg);
    font = 2;
    sprintf(msg, "%s", "1BI15CS012");
    msgtext(5 * n / 100, -30 * n / 100, 0, msg);
    font = 2;
    sprintf(msg, "%s", "PROF. POOJA RANGASWAMY");
    msgtext(160 * n / 100, -30 * n / 100, 0, msg);
    font = 2;
    sprintf(msg, "%s", "AJAY K");
    msgtext(5 * n / 100, -25 * n / 100, 0, msg);
    font = 2;
    sprintf(msg, "%s", "PROF. N THANUJA");
    msgtext(160 * n / 100, -25 * n / 100, 0, msg);
    font = 1;
    sprintf(msg, "%s", "BY:");
    msgtext(5 * n / 100, -20 * n / 100, 0, msg);
    font = 1;
    sprintf(msg, "%s", "UNDER THE GUIDANCE OF: ");
    msgtext(160 * n / 100, -20 * n / 100, 0, msg);
    /*switch (type)
    {
    case 'r':
        drawtext(0, n, 0, "Randomized");
        break;
    case 'q':
        drawtext(0, n, 0, "Quick Sort | Execution time in ms=");
        break;
    case 'b':
        drawtext(0, n, 0, "Bubble Sort | Execution time in ms=");
        break;
    case 'g':
        drawtext(0, n, 0, "Gravity Sort | Execution time in ms=");
        break;
    case 's':
        drawtext(0, n, 0, "Selection Sort | Execution time in ms=");
        break;
    case 'i':
        drawtext(0, n, 0, "Insertion Sort | Execution time in ms=");
        break;
    case 'h':
        drawtext(0, n, 0, "Heap Sort | Execution time in ms=");
        break;
    case 'm':
        drawtext(0, n, 0, "Merge Sort | Execution time in ms=");
        break;
    }
    for (i = 0; i < n; i++)
    {
        scale(a[i]);
        translate(i);
        nsq[0][0] = 0 + 2 * i;
        nsq[1][0] = 0;
        nsq[0][1] = 1 + 2 * i;
        nsq[1][1] = 0;
        cube();
    }*/
    glFlush();
    glutSwapBuffers();
}

void msgtext(int x, int y, int z, char *msg)
{
    int i;
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3i(x, y, z);
    if (font == 1)
    {
        for (i = 0; msg[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg[i]);
    }
    else if (font == 2)
    {
        for (i = 0; msg[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg[i]);
    }
    else if (font == 3)
    {
        for (i = 0; msg[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg[i]);
    }
}

void drawtext(int x, int y, int z, char *s)
{
    int i, j;
    char t[10];
    char *u = malloc(strlen(s) + 20);
    for (i = 0; i < strlen(u); i++)
        u[i] = ' ';
    if (type != 'r')
    {
        sprintf(t, "%d", (int)((clock() - start) / 1000));
        strcat(u, s);
        strcat(u, t);
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos3i(x, y, z);
        for (i = 0; u[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, u[i]);
    }
    else
    {
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos3i(x, y, z);
        for (i = 0; s[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        char m[150];
        sprintf(m, "%s", "1. Bubble | 2. Quick | 3. Gravity | 4. Selection | 5. Insertion | 6. Heap | 7. Merge");
        glRasterPos3i(x, y + 4, z);
        for (i = 0; m[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, m[i]);
    }
}

void bsort(int a[], int n)
{
    int i, j, x, y, temp;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
        {
            if (order == 'a')
            {
                if (a[i] > a[j])
                {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                    display();
                }
            }
            if (order == 'd')
            {
                if (a[i] < a[j])
                {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                    display();
                }
            }
            delay(100);
        }
}

void delay(int d)
{
    clock_t start = clock();
    while (clock() < start + d)
    {
    }
}

void quickSort(int a[], int n, int low, int high)
{
    if (low < high)
    {
        int pi = partition(a, n, low, high);
        quickSort(a, n, low, pi - 1);
        quickSort(a, n, pi + 1, high);
    }
}

extern int partition(int a[], int n, int low, int high)
{
    int pivot = a[high];
    int i = (low - 1), j;

    for (j = low; j <= high - 1; j++)
    {
        if (order == 'a')
        {
            if (a[j] <= pivot)
            {
                i++;
                swap(&a[i], &a[j]);
                display();
                delay(1000);
            }
        }
        if (order == 'd')
        {
            if (a[j] >= pivot)
            {
                i++;
                swap(&a[i], &a[j]);
                display();
                delay(1000);
            }
        }
    }
    swap(&a[i + 1], &a[high]);
    display();
    delay(1000);
    return (i + 1);
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void beadSort(int a[], int len)
{
    int max = a[0], i, j;
    for (i = 1; i < len; i++)
        if (a[i] > max)
            max = a[i];

    unsigned char beads[max * len];
    memset(beads, 0, sizeof(beads));

    for (i = 0; i < len; i++)
        for (j = 0; j < a[i]; j++)
        {
            BEAD(i, j) = 1;
        }

    for (j = 0; j < max; j++)
    {
        int sum = 0;
        for (i = 0; i < len; i++)
        {
            sum += BEAD(i, j);
            BEAD(i, j) = 0;
        }
        for (i = len - sum; i < len; i++)
            BEAD(i, j) = 1;
    }
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < max && BEAD(i, j); j++)
            ;
        a[i] = j;
        display();
        delay(1000);
    }
}

void selectionSort(int a[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (order == 'a')
            {
                if (a[j] < a[min_idx])
                    min_idx = j;
            }
            else
            {
                if (a[j] > a[min_idx])
                    min_idx = j;
            }
        }
        swap(&a[min_idx], &a[i]);
        delay(5000);
        display();
    }
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        if (order == 'a')
        {
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
                display();
                delay(100);
            }
        }
        else
        {
            while (j >= 0 && arr[j] < key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
                display();
                delay(100);
            }
        }

        arr[j + 1] = key;
    }
}

void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
    {
        if (order == 'a')
            heapify(arr, n, i);
        else
            heapifyd(arr, n, i);
    }

    // One by one extract an element from heap
    for (i = n - 1; i >= 0; i--)
    {
        // Move current root to end
        swap(&arr[0], &arr[i]);
        display();
        delay(100);

        // call max heapify on the reduced heap
        if (order == 'a')
            heapify(arr, i, 0);
        else
            heapifyd(arr, i, 0);
    }
}

void heapifyd(int arr[], int n, int i)
{
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] < arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] < arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        display();
        delay(1000);

        // Recursively heapify the affected sub-tree
        heapifyd(arr, n, largest);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        display();
        delay(1000);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (order == 'a')
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                display();
                delay(1000);
                i++;
            }
            else
            {
                arr[k] = R[j];
                display();
                delay(1000);
                j++;
            }
        }
        else
        {
            if (L[i] >= R[j])
            {
                arr[k] = L[i];
                display();
                delay(1000);
                i++;
            }
            else
            {
                arr[k] = R[j];
                display();
                delay(1000);
                j++;
            }
        }

        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        display();
        delay(1000);
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        display();
        delay(1000);
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
  *  sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void cube()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][0], nsq[1][0], 0);
    glVertex3i(nsq[0][1], nsq[1][1], 0);
    glVertex3i(nsq[0][2], nsq[1][2], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][0], nsq[1][0], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 1);
    glVertex3i(nsq[0][0], nsq[1][0], 1);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][1], nsq[1][1], 0);
    glVertex3i(nsq[0][2], nsq[1][2], 0);
    glVertex3i(nsq[0][2], nsq[1][2], 1);
    glVertex3i(nsq[0][1], nsq[1][1], 1);
    glEnd();

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][0], nsq[1][0], 1);
    glVertex3i(nsq[0][1], nsq[1][1], 1);
    glVertex3i(nsq[0][2], nsq[1][2], 1);
    glVertex3i(nsq[0][3], nsq[1][3], 1);
    glEnd();

    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][2], nsq[1][2], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 1);
    glVertex3i(nsq[0][2], nsq[1][2], 1);
    glEnd();

    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][0], nsq[1][0], 0);
    glVertex3i(nsq[0][1], nsq[1][1], 0);
    glVertex3i(nsq[0][1], nsq[1][1], 1);
    glVertex3i(nsq[0][0], nsq[1][0], 1);
    glEnd();
}

void multiply(char x)
{
    int i, j, k;
    if (x == 's')
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 4; j++)
            {
                nsq[i][j] = 0;
                for (k = 0; k < 4; k++)
                    nsq[i][j] += scalem[i][k] * osq[k][j];
            }
        }
        for (i = 0; i < 3; i++)
            for (j = 0; j < 4; j++)
                tsq[i][j] = nsq[i][j];
    }
    else
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 4; j++)
            {
                nsq[i][j] = 0;
                for (k = 0; k < 4; k++)
                    nsq[i][j] += transm[i][k] * tsq[k][j];
            }
        }
    }
}

void scale(int i)
{
    scalem[1][1] = i + 1;
    multiply('s');
}

void translate(int i)
{
    transm[0][2] = 2 * i;
    multiply('t');
}

void keys(unsigned char key, int x, int y)
{
    if (key == 13)
    {
        type = 'r';
        randomize(a, n);
    }
    if (key == '0')
    {
        type = 'r';
        randomize(a, n);
    }
    if (key == '1')
    {
        type = 'b';
        start = clock();
        bsort(a, n);
    }
    if (key == '2')
    {
        type = 'q';
        start = clock();
        quickSort(a, n, 0, n - 1);
    }
    if (key == '3')
    {
        type = 'g';
        start = clock();
        beadSort(a, n);
        display();
    }
    if (key == '4')
    {
        type = 's';
        start = clock();
        selectionSort(a, n);
        display();
    }
    if (key == '5')
    {
        type = 'i';
        start = clock();
        insertionSort(a, n);
        display();
    }
    if (key == '6')
    {
        type = 'h';
        start = clock();
        heapSort(a, n);
        display();
    }
    if (key == '7')
    {
        type = 'm';
        start = clock();
        mergeSort(a, 0, n);
        display();
    }
}

void SpecialInput(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        axis = 1;
        theta[axis] += 0.5;
        if (theta[axis] >= 360.0)
            theta[axis] -= 360.0;
        glRotatef(theta[0], 1.0, 0.0, 0.0);
        display();
    }
    if (key == GLUT_KEY_DOWN)
    {
        axis = 1;
        theta[axis] += 0.5;
        if (theta[axis] >= 360.0)
            theta[axis] -= 360.0;
        glRotatef(-theta[0], 1.0, 0.0, 0.0);
        display();
    }
    if (key == GLUT_KEY_LEFT)
    {
        axis = 0;
        theta[axis] += 0.5;
        if (theta[axis] >= 360.0)
            theta[axis] -= 360.0;
        glRotatef(theta[1], 0.0, 1.0, 0.0);
        display();
    }
    if (key == GLUT_KEY_RIGHT)
    {
        axis = 0;
        theta[axis] += 0.5;
        if (theta[axis] >= 360.0)
            theta[axis] -= 360.0;
        glRotatef(-theta[1], 0.0, 1.0, 0.0);
        display();
    }
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void randomize()
{
    srand(time(NULL));
    int i;
    for (i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&a[i], &a[j]);
    }
    display();
}

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, 2 * n, 0, n, 0, n);
}

void menu(int n)
{
    switch (n)
    {
    case 1:
        order = 'a';
        display();
        break;
    case 2:
        order = 'd';
        display();
        break;
    }
}

void main(int argc, char **argv)
{
    printf("Enter the number of elements you'd like to see: ");
    scanf("%d", &n);
    int i;
    a = malloc((n + 1) * sizeof(int));
    for (i = 0; i < n; i++)
        a[i] = i;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(2000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's");
    glutCreateMenu(menu);
    glutAddMenuEntry("Ascending", 1);
    glutAddMenuEntry("Descending", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    myInit();
    randomize(a, n);
    glutDisplayFunc(display1);
    glutReshapeFunc(myReshape);
    glutKeyboardFunc(keys);
    glutSpecialFunc(SpecialInput);
    //glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
