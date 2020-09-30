#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void displayStatInfo(struct stat *sb)
{
	printf("File type : ");
	switch (sb->st_mode & S_IFMT) {
		case S_IFREG: printf("regular file\n");break;
		case S_IFDIR: printf("directory\n");break;
		case S_IFCHR:
		case S_IFBLK:
		case S_IFLNK:
		case S_IFIFO:
		case S_IFSOCK:
		printf("Special file\n");break;
		default:
		printf("unknown type\n");break;
	}

	printf("major=%ld minor=%ld numbers\n",
	(long) major(sb->st_dev), (long) minor(sb->st_dev));
	printf("Inode number : %ld\n", (long) sb->st_ino);

	printf("File size : %lld bytes\n", (long long) sb->st_size);
	printf("Optimal I/O block size : %ld bytes\n",
						(long) sb->st_blksize);
	printf("Allocated blocks (512 bytes each) : %lld\n",
						(long long) sb->st_blocks);
}

int main(int argc, char *argv[]){
	struct stat fileStat;

	// Récupérer les métadonnées du fichier
	if (stat(argv[1], &fileStat) < 0){
		perror("stat");
		exit(EXIT_FAILURE);
	}
	
	 // Afficher les métadonnées.
	displayStatInfo(&fileStat);

	return EXIT_SUCCESS;
}


