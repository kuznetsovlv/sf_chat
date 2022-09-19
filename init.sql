create user 'sfchat'@'localhost' identified by 'sfchatpassword';
create database sfchatdb;
grant all privileges on sfchatdb.* to 'sfchat'@'localhost' with grant option;
flush privileges;
use sfchatdb;

create table users(id int not null auto_increment unique, login varchar(255) not null unique, full_name varchar(255), sha1 varchar(255) not null, primary key (id));
create table messages(id int not null auto_increment unique, from_user_id int, to_user_id int, text varchar(1023), date datetime default(now()), primary key(id));
