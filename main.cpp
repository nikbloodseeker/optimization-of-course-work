#define _CRT_SECURE_NO_WARNINGS
#include <GLFW/glfw3.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 
#include <math.h>
float x = 0;
float y = 0;
float xAlpha = 0.1;
float yAlpha = 0.1;

int Height = 1000;
int Width = 1000;

const double Pi = 3.14159265358979323846264338327950288419716939937510;

//Алгоритм на старнице 1
void simplification_function(char* str, int len)
{
    int multiplication_index = 0, division_index = 0, k = 0, j = 0;
    char chislo1[100], chislo2[100];
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '*')
        {
            multiplication_index = i;
            if (str[i + 1] >= 48 && str[i + 1] <= 57)//Если элемент цифра
            {
                i++;
                while (str[i] >= 48 && str[i] <= 57)
                    i++;
                if (str[i] == '/')
                {
                    /*Далее я буду писать код , который позволит скпоировать множитель и делитель соответственно в chislo1,chislo2 и сравнить*/


                    division_index = i;
                    if (str[multiplication_index - 1] >= 48 && str[multiplication_index - 1] <= 57)//Если символ до умножения цифра,то копирую все цифры в chislo1
                    {
                        k = multiplication_index - 1;//присваиваю k индекс цифры
                        j = 0;//Итератор chislo1
                        while (str[k] >= 48 && str[k] <= 57)
                        {
                            chislo1[j] = str[k];
                            j++;
                            k--;
                        }

                    }
                    else if (str[multiplication_index - 1] == ')')////Если символ до умножения закрывающая скобка, то копирую в chislo1 содержимое скобок
                    {
                        k = multiplication_index - 1;//присваиваю k индекс скобки
                        j = 0;//Итератор chislo1
                        do
                        {
                            if (str[k] == '(')
                            {
                                do
                                {
                                    chislo1[j] = str[k];
                                    j++;
                                    k--;
                                } while (str[k] != '(');
                            }
                        } while (str[k] != '(');
                    }

                }
            }
            else if (str[i + 1] == '(')
            {
                i += 2;//индекс , на следующий элемент посое '('
                while (str[i] != ')')
                {
                    if (str[i] == '(')
                    {
                        while (str[i] != ')')
                        {
                            i++;
                        }
                    }
                }
                if (str[i] == '/')
                {
                    /*То я должен скопировать все , что до знака умножения и все , что после знака деления. Затем сравнивать и сократить
                    , если такая возможность есть*/
                }
            }

        }
    }
}

void Documentation()
{

    printf("\tA program for plotting functions\n"
        "\t\tGuide:\n"
        "1.Supported functions:\n"
        "\t '+' - addition, '-' - subtraction, '*' - multiplication, '/' - division\n"
        "\t '()' - parentheses (Each opening parenthesis must have a closing one)\n"
        "\t '^' - exponentiation\n"
        "\t 'sin()','cos()','tan()','ctg()' - trigonometric functions\n"
        "\t 'exp()' - exponent (exp(1) - exponent of the 1st degree)\n"
        "2.Functional:\n"
        "\tPlotting functions\n"
        "\t\tEnter the function: ");
}

typedef struct Node {
    double value;
    char operation;
    struct Node* pNext;
}Node;

int push(Node** top, double value, char operation) {
    char opertion = 0;
    Node* pNew = (Node*)malloc(sizeof(Node));
    pNew->value = value;
    pNew->operation = operation;
    if (*top == NULL) {
        pNew->pNext = NULL;
        *top = pNew;
    }
    else {
        pNew->pNext = *top;
        *top = pNew;
    }
    return 0;
}
int pop(Node** top) {
    if (top == NULL) {
        return 0;
    }
    Node* tmp = *top;
    *top = tmp->pNext;
    free(tmp);
    return 0;
}
void CreateAxis()
{
    glLineWidth(5);

    glBegin(GL_LINES);
    //x
    glColor3f(1, 0, 0);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    //y
    glColor3f(0, 1, 0);
    glVertex3f(0, -1, 0);
    glVertex3f(0, 1, 0);
    //z
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -1);
    glVertex3f(0, 0, 1);
    glEnd();


    glBegin(GL_TRIANGLE_FAN);
    //x
    glColor3f(1, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0.95, 0.02, 0);
    glVertex3f(0.95, 0, 0.02);
    glVertex3f(0.95, -0.02, 0);
    glVertex3f(0.95, 0, -0.02);
    glVertex3f(0.95, 0.02, 0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    //y
    glColor3f(0, 1, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(0.02, 0.95, 0);
    glVertex3f(0, 0.95, 0.02);
    glVertex3f(-0.02, 0.95, 0);
    glVertex3f(0, 0.95, -0.02);
    glVertex3f(0.02, 0.95, 0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    //z
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0.02, 0, 0.95);
    glVertex3f(0, 0.02, 0.95);
    glVertex3f(-0.02, 0, 0.95);
    glVertex3f(0, -0.02, 0.95);
    glVertex3f(0.02, 0, 0.95);
    glEnd();
}
void ControlAxis()
{
    if (GetKeyState(VK_UP) < 0)
        x += xAlpha;
    if (GetKeyState(VK_DOWN) < 0)
        x -= xAlpha;
    glRotatef(-x, 1, 0, 0);
    if (GetKeyState(VK_RIGHT) < 0)
        y += yAlpha;
    if (GetKeyState(VK_LEFT) < 0)
        y -= yAlpha;
    glRotatef(-y, 0, 0, 1);
}
bool Math(Node** top_n, Node** top_o)
{
    double a, b, c;
    Node* tmp_n; Node* tmp_o;
    tmp_n = *top_n;
    tmp_o = *top_o;
    a = tmp_n->value;
    pop(top_n);
    tmp_n = *top_n;
    switch (tmp_o->operation)
    {
    case '+':

        b = tmp_n->value;
        c = a + b;
        pop(top_o);
        pop(top_n);
        push(top_n, c, '0');
        break;
    case '-':
        b = tmp_n->value;
        c = b - a;
        pop(top_o);
        pop(top_n);
        push(top_n, c, '0');
        break;
    case '*':
        b = tmp_n->value;
        c = a * b;
        pop(top_o);
        pop(top_n);
        push(top_n, c, '0');
        break;
    case '/':
        b = tmp_n->value;
        if (a == 0)
        {
            printf("������ ������ �� ����!");
            return false;
        }
        else {
            c = b / a;
            pop(top_o);
            pop(top_n);
            push(top_n, c, '0');
            break;
        }
    case '^':
        b = tmp_n->value;
        c = pow(b, a);
        pop(top_o);
        pop(top_n);
        push(top_n, c, '0');
        break;
    case 's':
        c = sin(a);
        pop(top_o);
        push(top_n, c, '0');
        break;
    case 'c':
        c = cos(a);
        pop(top_o);
        push(top_n, c, '0');
        break;
    case 't':
        if (cos(a) == 0) {
            printf("������� �� ����������");
            return false;
        }
        c = tan(a);
        pop(top_o);
        push(top_n, c, '0');
        break;
    case 'e':
        c = exp(a);
        pop(top_o);
        push(top_n, c, '0');
        break;
    case 'g':
        if (sin(a) == 0) {
            printf("��������� �� ����������");
            return false;
        }
        c = 1 / tan(x);
        pop(top_o);
        push(top_n, c, '0');
        break;
    default:
        printf("����������� �������!");
        return false;
        break;

    }
    return true;
}
int getRang(char Ch)
{
    if (Ch == '+' || Ch == '-') return 1;
    if (Ch == '*' || Ch == '/') return 2;
    if (Ch == '^') return 3;
    if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e') return 4;
    return 0;
}

struct Point3D
{
    double x;
    double y;
    double z;
};
int parser(struct Point3D* Points)
{
    char operation = 0;
    char Ch;
    double value;
    bool flag = 1;
    Node* top_n = NULL;
    Node* top_o = NULL;

    char function[100];
    scanf("%s", function);

    function[strlen(function)] = '\n';



    int pointCount = 0;
    for (double xParam = -8; xParam < 8; xParam += 0.15)
    {
        for (double yParam = -8; yParam < 8; yParam += 0.15)
        {
            for (int s = 0; s <= strlen(function); )
            {
                Ch = function[s];
                if (Ch == '\n')
                    break;
                if (Ch == ' ')
                    s++;
                if (Ch == 'x')
                {
                    push(&top_n, xParam, '0');
                    s++;
                    continue;
                }
                if (Ch == 'y')
                {
                    push(&top_n, yParam, '0');
                    s++;
                    continue;
                }
                if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'e')
                {
                    char chars[3];
                    for (int n = 0; n < 3; n++)
                    {
                        Ch = function[s++];
                        chars[n] = Ch;
                    }
                    if (chars[0] == 's' && chars[1] == 'i' && chars[2] == 'n')
                    {
                        push(&top_o, 0, 's');
                        continue;
                    }
                    if (chars[0] == 'c' && chars[1] == 'o' && chars[2] == 's')
                    {
                        push(&top_o, 0, 'c');
                        continue;
                    }
                    if (chars[0] == 't' && chars[1] == 'a' && chars[2] == 'n')
                    {
                        push(&top_o, 0, 't');
                        continue;
                    }
                    if (chars[0] == 'c' && chars[1] == 't' && chars[2] == 'g')
                    {
                        push(&top_o, 0, 'g');
                        continue;
                    }
                    if (chars[0] == 'e' && chars[1] == 'x' && chars[2] == 'p')
                    {
                        push(&top_o, 0, 'e');
                        continue;
                    }
                }
                if (Ch >= '0' && Ch <= '9')
                {
                    double value;
                    char num[100] = { 0 };
                    int j = 0;
                    while (isdigit(function[s]) || function[s] == '.')
                    {
                        num[j] = function[s];
                        s++;
                        j++;
                    }
                    value = atof(num); // ����������� ������ � �����  � ����������� ���������� ���� float
                    push(&top_n, value, '0');
                    continue;
                }
                if (Ch == '+' || Ch == '-' || Ch == '*' || Ch == '/' || Ch == '^')
                {
                    float value = 0;
                    char operation = 0;
                    if (top_o != NULL && getRang(Ch) > getRang(top_o->operation))
                    {
                        push(&top_o, 0, Ch);
                        s++;
                        continue;
                    }
                    if (top_o != NULL && getRang(Ch) <= getRang(top_o->operation))
                    {
                        if (!Math(&top_n, &top_o))
                        {
                            system("pause");
                            return 0;
                        }
                        continue;
                    }
                    if (top_o == 0) {
                        push(&top_o, 0, Ch);
                        s++;
                        continue;
                    }

                }
                if (Ch == '(') {

                    push(&top_o, 0, Ch);

                    s++;
                    continue;
                }
                if (Ch == ')') {
                    while (top_o->operation != '(') {
                        if (!Math(&top_n, &top_o)) {
                            system("pause");
                            return 0;
                        }
                        else continue;
                    }
                    //�������� ������
                    pop(&top_o);
                    s++;
                    continue;
                }

            }
            while (top_o != NULL) {
                Math(&top_n, &top_o);
            }
            if (top_n != NULL)
            {
                struct Point3D newPoint;
                newPoint.x = xParam;
                newPoint.y = yParam;
                newPoint.z = top_n->value;
                Points[pointCount++] = newPoint;
                pop(&top_n);
            }
        }
    }
    return  pointCount;
}
int main()
{
    system("chcp 1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Documentation();

    struct Point3D Points[20000];
    int pointCount = parser(Points);

    printf("X"
        "|\t"
        "Y"
        "|\t"
        "Z");
    for (int i = 0; i < 441; i++)
        printf("%g \t| %g \t| %g\n", Points[i].x, Points[i].y, Points[i].z);










    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(Width, Height, "FunctionGraph", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(-90, 1, 0, 0);

        glPushMatrix();



        ControlAxis();
        CreateAxis();
        glPointSize(5);
        glBegin(GL_POINTS);
        glColor3f(0, 0, 1);
        for (int p = 0; p <= pointCount; p++)
            glVertex3f(Points[p].x * 0.1, Points[p].y * 0.1, Points[p].z * 0.1);
        glEnd();

        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}