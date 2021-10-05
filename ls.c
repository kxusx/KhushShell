#include "ls.h"
#include "headers.h"
#include "utils.h"

void lsP(char args[1000][1000])
{
    struct stat stats;
    int lflag = 0;
    int aflag = 0;
    char paths[500][500];
    char DirPath[100];
    long long int total = 0;
    char filePath[100];
    char Buffer[100];
    int counter = 0;
    int j = 1;
    char CurrentDir[5000];
    getcwd(CurrentDir, sizeof(CurrentDir));

    while (j < i)
    {
        if (strcmp(args[j], "-l") == 0)
            lflag = 1;
        else if (strcmp(args[j], "-a") == 0)
            aflag = 1;
        else if ((strcmp(args[j], "-la") == 0) || (strcmp(args[j], "-al") == 0))
        {
            lflag = 1;
            aflag = 1;
        }
        else if (strcmp(args[j], "~") == 0)
        {
            strcpy(paths[counter], HomeDir);
            counter++;
        }
        else
        {
            strcpy(paths[counter], args[j]);
            counter++;
        }
        j++;
    }

    if (counter == 0)
    {
        strcpy(paths[counter], CurrentDir);
        counter++;
    }

    int fileflag = 0;
    //looping thro given dir/files
    for (int k = 0; k < counter; k++)
    {
        DIR *lsdir;
        struct dirent *sd;
        DIR *lsdir_t;
        struct dirent *sd_t;
        //printf("Paths[%d]:%s\n", k, paths[k]);
        lsdir = opendir(paths[k]);

        if (lsdir == NULL)
        {
            if (access(paths[k], F_OK) == 0)
            {
                fileflag = 1;
            }
            else
            {
                sprintf(Buffer, "ls:%s", paths[k]);
                perror(Buffer);
                continue;
            }
        }
        else
        {
            strcpy(DirPath, paths[k]);
        }

        // if file
        if (fileflag == 1)
        {
            strcpy(filePath, CurrentDir);
            strcat(filePath, "/");
            strcat(filePath, paths[k]);
            if (lflag == 1)
            {
                lstat(filePath, &stats);
                strcpy(Buffer, "");
                struct passwd *pass = getpwuid(stats.st_uid);
                struct group *grp = getgrgid(stats.st_gid);
                S_ISDIR(stats.st_mode) ? strcat(Buffer, "d") : strcat(Buffer, "-");
                (stats.st_mode & S_IRUSR) ? strcat(Buffer, "r") : strcat(Buffer, "-");
                (stats.st_mode & S_IWUSR) ? strcat(Buffer, "w") : strcat(Buffer, "-");
                (stats.st_mode & S_IXUSR) ? strcat(Buffer, "x") : strcat(Buffer, "-");
                (stats.st_mode & S_IRGRP) ? strcat(Buffer, "r") : strcat(Buffer, "-");
                (stats.st_mode & S_IWGRP) ? strcat(Buffer, "w") : strcat(Buffer, "-");
                (stats.st_mode & S_IXGRP) ? strcat(Buffer, "x") : strcat(Buffer, "-");
                (stats.st_mode & S_IROTH) ? strcat(Buffer, "r") : strcat(Buffer, "-");
                (stats.st_mode & S_IWOTH) ? strcat(Buffer, "w") : strcat(Buffer, "-");
                (stats.st_mode & S_IXOTH) ? strcat(Buffer, "x") : strcat(Buffer, "-");

                printf("%s %3hu ", Buffer, stats.st_nlink);
                printf("%s ", pass->pw_name);
                printf("%s ", grp->gr_name);
                printf("%6lld ", stats.st_size);
                // char gettime[500];
                // strcpy(gettime, ctime(&stats.st_mtime));
                // gettime[strcspn(gettime, "\n")] = 0;
                // printf("%10s ", gettime);
                time_t present = time(NULL);
                struct tm time_l, time_p;
                char time_val[256];
                localtime_r(&stats.st_mtime, &time_l);
                localtime_r(&present, &time_p);

                if (time_l.tm_year != time_p.tm_year)
                {
                    strftime(time_val, sizeof(time_val), "%b %e %Y", localtime(&stats.st_mtime));
                }
                else
                {
                    strftime(time_val, sizeof(time_val), "%b %e %H:%M", localtime(&stats.st_mtime));
                }
                printf(" %s ", time_val);

                printf("%s\n", paths[k]);
            }
            else
            {
                printf("%s\n", paths[k]);
            }
        }
        // if not file
        else
        {
            if (DirPath[strlen(DirPath) - 1] == '/' && strlen(DirPath) > 1)
            {
                DirPath[strlen(DirPath) - 1] = '\0';
            }
            // printf("DirPath : %s\n", DirPath);
            lsdir = opendir(DirPath);

            if (lsdir == NULL)
            {
                sprintf(Buffer, "ls:%s", paths[k]);
                perror(Buffer);
                continue;
            }
            //lflag = 1 aflag = 1
            else if (aflag == 1 && lflag == 1)
            {
                while ((sd = readdir(lsdir)) != NULL)
                {
                    strcpy(filePath, DirPath);
                    strcat(filePath, "/");
                    strcat(filePath, sd->d_name);
                    //printf("FilePath:%s\n", filePath);
                    lstat(filePath, &stats);
                    total += stats.st_blocks;
                }
                printf("total %lld\n", total);
                lsdir = opendir(DirPath);

                while ((sd = readdir(lsdir)) != NULL)
                {

                    strcpy(filePath, DirPath);
                    strcat(filePath, "/");
                    strcat(filePath, sd->d_name);

                    lstat(filePath, &stats);
                    struct passwd *pass = getpwuid(stats.st_uid);
                    struct group *grp = getgrgid(stats.st_gid);
                    //printf("hu2");
                    strcpy(Buffer, "");
                    S_ISDIR(stats.st_mode) ? strcat(Buffer, "d") : strcat(Buffer, "-");
                    (stats.st_mode & S_IRUSR) ? strcat(Buffer, "r") : strcat(Buffer, "-");
                    (stats.st_mode & S_IWUSR) ? strcat(Buffer, "w") : strcat(Buffer, "-");
                    (stats.st_mode & S_IXUSR) ? strcat(Buffer, "x") : strcat(Buffer, "-");
                    (stats.st_mode & S_IRGRP) ? strcat(Buffer, "r") : strcat(Buffer, "-");
                    (stats.st_mode & S_IWGRP) ? strcat(Buffer, "w") : strcat(Buffer, "-");
                    (stats.st_mode & S_IXGRP) ? strcat(Buffer, "x") : strcat(Buffer, "-");
                    (stats.st_mode & S_IROTH) ? strcat(Buffer, "r") : strcat(Buffer, "-");
                    (stats.st_mode & S_IWOTH) ? strcat(Buffer, "w") : strcat(Buffer, "-");
                    (stats.st_mode & S_IXOTH) ? strcat(Buffer, "x") : strcat(Buffer, "-");
                    //printf("hu3");

                    printf("%s %3hu ", Buffer, stats.st_nlink);
                    printf("%s ", pass->pw_name);
                    printf("%s ", grp->gr_name);
                    printf("%6lld ", stats.st_size);
                    // char gettime[500];
                    // strcpy(gettime, ctime(&stats.st_mtime));
                    // gettime[strcspn(gettime, "\n")] = 0;
                    // printf("%10s ", gettime);

                    time_t present = time(NULL);
                    struct tm time_l, time_p;
                    char time_val[256];
                    localtime_r(&stats.st_mtime, &time_l);
                    localtime_r(&present, &time_p);

                    if (time_l.tm_year != time_p.tm_year)
                    {
                        strftime(time_val, sizeof(time_val), "%b %e %Y", localtime(&stats.st_mtime));
                    }
                    else
                    {
                        strftime(time_val, sizeof(time_val), "%b %e %H:%M", localtime(&stats.st_mtime));
                    }
                    printf(" %s ", time_val);

                    printf("%s \n", sd->d_name);
                }
            }
            //aflag =1
            else if (aflag == 1)
            {
                while ((sd = readdir(lsdir)) != NULL)
                {
                    printf("%s\n", sd->d_name);
                }
            }
            //lflag = 1
            else if (lflag == 1)
            {
                //printf("la flag activated\n");
                while ((sd = readdir(lsdir)) != NULL)
                {
                    if (sd->d_name[0] != '.')
                    {
                        strcpy(filePath, DirPath);
                        strcat(filePath, "/");
                        strcat(filePath, sd->d_name);
                        //printf("FilePath:%s\n", filePath);
                        lstat(filePath, &stats);
                        total += stats.st_blocks;
                    }
                }
                printf("total %lld\n", total);
                lsdir = opendir(DirPath);

                while ((sd = readdir(lsdir)) != NULL)
                {
                    if (sd->d_name[0] != '.')
                    {
                        strcpy(filePath, DirPath);
                        strcat(filePath, "/");
                        strcat(filePath, sd->d_name);

                        lstat(filePath, &stats);
                        struct passwd *pass = getpwuid(stats.st_uid);
                        struct group *grp = getgrgid(stats.st_gid);
                        //printf("hu2");
                        strcpy(Buffer, "");
                        S_ISDIR(stats.st_mode) ? strcat(Buffer, "d") : strcat(Buffer, "-");
                        (stats.st_mode & S_IRUSR) ? strcat(Buffer, "r") : strcat(Buffer, "-");
                        (stats.st_mode & S_IWUSR) ? strcat(Buffer, "w") : strcat(Buffer, "-");
                        (stats.st_mode & S_IXUSR) ? strcat(Buffer, "x") : strcat(Buffer, "-");
                        (stats.st_mode & S_IRGRP) ? strcat(Buffer, "r") : strcat(Buffer, "-");
                        (stats.st_mode & S_IWGRP) ? strcat(Buffer, "w") : strcat(Buffer, "-");
                        (stats.st_mode & S_IXGRP) ? strcat(Buffer, "x") : strcat(Buffer, "-");
                        (stats.st_mode & S_IROTH) ? strcat(Buffer, "r") : strcat(Buffer, "-");
                        (stats.st_mode & S_IWOTH) ? strcat(Buffer, "w") : strcat(Buffer, "-");
                        (stats.st_mode & S_IXOTH) ? strcat(Buffer, "x") : strcat(Buffer, "-");
                        //printf("hu3");

                        printf("%s %3hu ", Buffer, stats.st_nlink);
                        printf("%s ", pass->pw_name);
                        printf("%s ", grp->gr_name);
                        printf("%6lld ", stats.st_size);

                        // char gettime[500];
                        // strcpy(gettime, ctime(&stats.st_mtime));
                        // gettime[strcspn(gettime, "\n")] = 0;
                        // printf("%10s ", gettime);

                        time_t present = time(NULL);
                        struct tm time_l, time_p;
                        char time_val[256];
                        localtime_r(&stats.st_mtime, &time_l);
                        localtime_r(&present, &time_p);

                        if (time_l.tm_year != time_p.tm_year)
                        {
                            strftime(time_val, sizeof(time_val), "%b %e %Y", localtime(&stats.st_mtime));
                        }
                        else
                        {
                            strftime(time_val, sizeof(time_val), "%b %e %H:%M", localtime(&stats.st_mtime));
                        }
                        printf(" %s ", time_val);

                        printf("%s \n", sd->d_name);
                    }
                }
            }
            //normal ls
            else
            {
                while ((sd = readdir(lsdir)) != NULL)
                {
                    if (sd->d_name[0] != '.')
                        printf("%s\n", sd->d_name);
                }
            }
        }
    }
    //printf("\n");
}
