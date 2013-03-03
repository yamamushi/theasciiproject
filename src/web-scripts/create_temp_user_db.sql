// create_temp_user_db.sql
// Set which database to use.
use ascii_project;

// Create temporary (unconfirmed) user table 
CREATE TABLE `temp_members_db` (
`confirm_code` varchar(65) NOT NULL default '',
`name` varchar(65) NOT NULL default '',
`email` varchar(65) NOT NULL default '',
`password` varchar(15) NOT NULL default '',
`country` varchar(65) NOT NULL default '',
`registered` datetime NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
