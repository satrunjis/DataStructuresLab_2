#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>

const wchar_t *fz[16] = {L"Иванов", L"Петров", L"Сидоров", L"Смирнов",
                         L"Кузнецов", L"Попов", L"Васильев", L"Михайлов",
                         L"Новиков", L"Федоров", L"Морозов", L"Волков",
                         L"Алексеев", L"Лебедев", L"Семенов", L"Егоров"};

const wchar_t *iz[16] = {L"Иван", L"Петр", L"Сидор", L"Олег",
                         L"Артем", L"Алексей", L"Дмитрий", L"Сергей",
                         L"Андрей", L"Михаил", L"Александр", L"Егор",
                         L"Константин", L"Виктор", L"Николай", L"Максим"};

const wchar_t *oz[16] = {L"Иванович", L"Петрович", L"Сидорович", L"Олегович",
                         L"Артемович", L"Алексеевич", L"Дмитриевич", L"Сергеевич",
                         L"Андреевич", L"Михайлович", L"Александрович", L"Егорович",
                         L"Константинович", L"Викторович", L"Николаевич", L"Максимович"};

const wchar_t *birthdate[16] = {L"01.01.2000", L"02.02.2001", L"03.03.2002", L"04.04.2003",
                                L"05.05.2004", L"06.06.2005", L"07.07.2006", L"08.08.2007",
                                L"09.09.2008", L"10.10.2009", L"11.11.2010", L"12.12.2011",
                                L"13.01.2012", L"14.02.2013", L"15.03.2014", L"16.04.2015"};

const wchar_t *numgroup[16] = {L"101", L"102", L"103", L"104",
                               L"105", L"106", L"107", L"108",
                               L"109", L"110", L"111", L"112",
                               L"113", L"114", L"115", L"116"};

const wchar_t *subjects_name[16] = {L"Математика", L"Физика", L"Химия", L"Информатика",
                                    L"История", L"Биология", L"Литература", L"География",
                                    L"Философия", L"Экономика", L"Социология", L"Право",
                                    L"Психология", L"Логика", L"Астрономия", L"Экология"};

const wchar_t *numcabl[16] = {L"101", L"102", L"103", L"104",
                              L"105", L"106", L"107", L"108",
                              L"109", L"110", L"111", L"112",
                              L"113", L"114", L"115", L"116"};

const wchar_t *numcabex[16] = {L"201", L"202", L"203", L"204",
                               L"205", L"206", L"207", L"208",
                               L"209", L"210", L"211", L"212",
                               L"213", L"214", L"215", L"216"};

const wchar_t *hours[16] = {L"36", L"48", L"72", L"24",
                            L"60", L"90", L"45", L"30",
                            L"15", L"50", L"55", L"40",
                            L"80", L"100", L"25", L"120"};

const wchar_t *attestatio[16] = {L"Экзамен", L"Зачет", L"Курсовая", L"Практика",
                                 L"Коллоквиум", L"Реферат", L"Тест", L"Диплом",
                                 L"Лабораторная", L"Контрольная", L"Доклад", L"Проект",
                                 L"Эссе", L"Собеседование", L"Рецензия", L"Опрос"};

typedef struct subjects {
    unsigned char name:4;
    unsigned char numcabl:4;
    unsigned char numcabex:4;
    unsigned char hours:4;
    unsigned char attestatio:4;
    unsigned char end:1;
} subjects;

typedef struct bd {
    unsigned char f:4;
    unsigned char i:4;
    unsigned char o:4;
    unsigned char birthdate:4;
    unsigned char numgroup:4;
    subjects* items;
} bd;

unsigned long long genn(bd *mas, int n, int min, int max) {
    srand(time(NULL));
    unsigned char *to_g = malloc(n);
    if (!to_g) {
        printf("Ошибка выделения памяти!\n");
        return 0;
    }
    
    unsigned long long maxcount = 0;
    int *masive = (int *)mas;
    for (int i = 0; i < n; i++, masive += 4) {
        *masive = rand();
        to_g[i] = min + (rand() % (max - min));
        maxcount += to_g[i];
    }
    
    subjects *mas2 = malloc(sizeof(subjects) * maxcount);
    if (!mas2) {
        printf("Ошибка выделения памяти для предметов!\n");
        free(to_g);
        return 0;
    }
    
    subjects *ptr = mas2;
    for (int i = 0; i < n; i++) {
        mas[i].items = ptr;
        for (int j = 0; j < to_g[i]; j++, ptr++) {
            *((int*)ptr) = rand();
            ptr->end = 1;
        }
        (ptr++)->end = 0;
    }
    free(to_g);
    return maxcount;
}

void print_students(bd *mas, int n) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wprintf(L"Фамилия  | Имя      | Отчество      | Дата рождения | НомГруп | Предмет     | НомКабЛек | НомКабЭкз | Часы | Вид аттестации\n");
    subjects *ptr;
    for (int i = 0; i < n; i++) {
        wprintf(L"%-9ls|%-10ls|%-15ls|%-15ls|%-7ls%ls\n",fz[mas[i].f], iz[mas[i].i], oz[mas[i].o], birthdate[mas[i].birthdate], numgroup[mas[i].numgroup],L"<-┓");        
        ptr = mas[i].items;
        do {
            wprintf(L"%-62ls|- %-11ls|%-11ls|%-11ls|%-6ls| %ls\n",L" ",subjects_name[ptr->name], numcabl[ptr->numcabl], numcabex[ptr->numcabex], hours[ptr->hours], attestatio[ptr->attestatio]);
        } while ((++ptr)->end);
    }
}

void read_the_command(){
    int nm=0, min_disciplines = 10, max_disciplines = 20,to_print_students=0;
    unsigned long long cont_predmetov=0,massive_size=0;
    char command[50];
    bd *mas=NULL;
    printf("Введите команду/ы:\n");
    while(fgets(command, sizeof(command), stdin) != NULL){
        if(strncmp(command,"gen",3) == 0){
            sscanf(command, "%*s %d --%d --%d", &nm, &min_disciplines, &max_disciplines);
            //sscanf(command, "%*s %d", &nm);
            mas = (bd *)malloc(sizeof(bd) * nm);
            if (!mas) {printf("Ошибка выделения памяти");return;}
            cont_predmetov=genn(mas, nm, min_disciplines, max_disciplines);
        }else if(strncmp(command,"print_students",14) == 0&&mas!=NULL){
            sscanf(command, "%*s %d", &to_print_students);
            print_students(mas, to_print_students==-1?nm:to_print_students);
        }else if(strncmp(command,"get_size",8) == 0){
            massive_size=sizeof(bd) * nm+cont_predmetov*sizeof(subjects);
            printf("Размер массива:%llu B ~ %llu Kb ~ %llu Mb ~ %llu Gb\n",massive_size,massive_size>>10,massive_size>>20,massive_size>>30);
        }else if(strncmp(command,"сlean",5) == 0){
            free(mas[0].items);
            free(mas);
            mas=NULL;
        }
    }
}

int main() {
    printf("Размер одного блока предмета: %zu Б\nРазмер одного блока Пользователя: %zu Б\n",sizeof(subjects), sizeof(bd));
    read_the_command();
    return 0;
}
