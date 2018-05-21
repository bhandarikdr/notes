#notes
<<<<<<< HEAD
======
=======
=====
>>>>>>> e5a1b247be8fa4df0820b4798bdedd49286b59f6
```bash
Terminal based notes keeping app with mysql database.
< needed: "Mysql" >
```
##uses
<<<<<<< HEAD
======
```bash
$ ./notes			==> lists all notes
$ ./notes <id>			==> displays note identified by <id>
$ ./notes -a|-add		==> adds notes 
$ ./notes -c|-configure		==> creates database and table
$ ./notes -h|-help		==> uses help 
=======
=====
```bash
$ ./notes		            ==> lists all notes
$ ./notes <id>		      ==> displays note identified by <id>
$ ./notes -a|-add	      ==> adds notes 
$ ./notes -c|-configure	==> creates database and table
$ ./notes -h|-help	    ==> uses help 
>>>>>>> e5a1b247be8fa4df0820b4798bdedd49286b59f6

$ ./notes -t|-truncate
```

##compile
<<<<<<< HEAD
=========
=======
=======
>>>>>>> e5a1b247be8fa4df0820b4798bdedd49286b59f6
```bash
$ gcc notes.c -o notes `mysql_config --cflags --libs`
```

##troubleshoot
<<<<<<< HEAD
==============
=======
============
>>>>>>> e5a1b247be8fa4df0820b4798bdedd49286b59f6
```bash
> DROP USER 'ntuser'@'localhost';

> DROP DATABASE notesdb;

> ALTER TABLE mynotes auto_increment=<value>;
```


