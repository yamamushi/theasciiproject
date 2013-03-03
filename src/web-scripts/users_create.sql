// Create registered user table
CREATE TABLE `users` (
`id` int(11) NOT NULL auto_increment,
`name` varchar(65) NOT NULL default '',
`email` varchar(65) NOT NULL default '',
`password` varchar(65) NOT NULL default '',
`country` varchar(65) NOT NULL default '',
`registered` datetime NOT NULL default '',
`permissions` int(10) NOT NULL default '',
PRIMARY KEY (`id`),
SECONDARY KEY (`permissions`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;


// Note on permissions levels: 1 is root, 5 is admin, 10 is user
// insert Admin users,


INSERT INTO users VALUES (1, 'root', 'root@theasciiproject.org, md5('N0p4ssW0rd4y0u!'), 'US', '2013-3-2 10:56:10', '1');
INSERT INTO users VALUES (2, 'yamamushi', 'yamamushi@gmail.com', md5('ar4nd0mp4ssw0rd!'), 'US', '2013-3-2 10:56:10', '5');
