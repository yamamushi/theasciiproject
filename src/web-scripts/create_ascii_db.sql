CREATE DATABASE ascii_project;
use ascii_project;
grant usage on *.* to fall3nsp0rk@localhost;
CREATE TABLE `users` (
`id` int(11) NOT NULL auto_increment,
`name` varchar(65) NOT NULL default '',
`email` varchar(65) NOT NULL default '',
`password` varchar(65) NOT NULL default '',
`country` varchar(65) NOT NULL default '',
`registered` datetime NOT NULL default '0-0-0 0:0:0',
`permissions` int(10) NOT NULL default '10',
PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
INSERT INTO users VALUES (1, 'root', 'root@theasciiproject.org', md5("N0p4ssW0rd4y0u!"), "US", "2013-3-2 10:56:10", "1");
INSERT INTO users VALUES (2, "yamamushi", "yamamushi@gmail.com", md5("ar4nd0mp4ssw0rd!"), "US", "2013-3-2 10:56:10", "5");
use ascii_project;
CREATE TABLE `temp_members_db` (
`confirm_code` varchar(65) NOT NULL default '',
`name` varchar(65) NOT NULL default '',
`email` varchar(65) NOT NULL default '',
`password` varchar(15) NOT NULL default '',
`country` varchar(65) NOT NULL default '',
`registered` datetime NOT NULL default '0-0-0 0:0:0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
