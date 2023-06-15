INSERT INTO Tusers (e_mail, password, role, fName, lName, dob)
VALUES ('hansmueller@web.com', 'password123', 'user', 'Hans', 'Mueller', '1990-01-29');

INSERT INTO Tusers (e_mail, password, role, fName, lName, dob)
VALUES ('mati@web.com', '123password', 'admin', 'Tadeus', 'Freitag', '1999-04-11');

INSERT INTO Tusers (e_mail, password, role, fName, lName, dob)
VALUES ('nico@web.com', '123password', 'admin', 'Nico', 'Epp', '2000-09-27');

INSERT INTO Tgroups(founder_id, created_at, updated_at)
VALUES (1, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);

INSERT INTO Tgroups(founder_id, created_at, updated_at)
VALUES (2, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);

INSERT INTO Tgroups(founder_id, created_at, updated_at)
VALUES (3, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);

INSERT INTO Tgroupmembers (group_id, permissions, user_id)
VALUES (1, 'r', 1);

INSERT INTO Tgroupmembers (group_id, permissions, user_id)
VALUES (2, 'rw', 2);

INSERT INTO Tgroupmembers (group_id, permissions, user_id)
VALUES (2, 'rw', 3);

INSERT INTO Tdirectory (group_id, user_id, name, subdir_id, created_at, updated_at)
VALUES (1, 1, 'Directory_1', 0, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);

INSERT INTO Tdirectory (group_id, user_id, name, subdir_id, created_at, updated_at)
VALUES (1, 1, 'Directory_2', 0, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);

INSERT INTO Tdirectory (group_id, user_id, name, subdir_id, created_at, updated_at)
VALUES (2, 2, 'Directory_1', 0, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);

INSERT INTO Tfiles (directory_id, file_size, store_path)
VALUES (1, 1000, '/path/to/file1.txt');

INSERT INTO Tfiles (directory_id, file_size, store_path)
VALUES (2, 1000, '/path/to/file2.txt');