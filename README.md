#notes
======
```bash
Terminal based notes keeping app with mysql database.
< needed: "Mysql" >
```
##uses
======
```bash
$ ./notes			==> lists all notes
$ ./notes <id>			==> displays note identified by <id>
$ ./notes -a|-add		==> adds notes 
$ ./notes -c|-configure		==> creates database and table
$ ./notes -h|-help		==> uses help 
<<<<<<< HEAD
$ ./notes -t|-truncate		==> clean database entries[WARNING]
=======
$ ./notes -t|-truncate
>>>>>>> 65e250f0b7e0d11ad6e4f9dcafbe3762eba3b154
```

##compile
=========
```bash
$ gcc notes.c -o notes `mysql_config --cflags --libs`
```

##troubleshoot
==============
```bash
> DROP USER 'ntuser'@'localhost';

> DROP DATABASE notesdb;

> ALTER TABLE mynotes auto_increment=<value>;
```
