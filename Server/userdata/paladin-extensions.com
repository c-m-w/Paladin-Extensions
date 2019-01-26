--- 
customlog: 
  - 
    format: combined
    target: /etc/apache2/logs/domlogs/paladin-extensions.com
  - 
    format: "\"%{%s}t %I .\\n%{%s}t %O .\""
    target: /etc/apache2/logs/domlogs/paladin-extensions.com-bytes_log
documentroot: /home/palavpvb/public_html
group: palavpvb
hascgi: 1
homedir: /home/palavpvb
ip: 198.54.120.180
owner: wh
phpopenbasedirprotect: 1
port: 81
scriptalias: 
  - 
    path: /home/palavpvb/public_html/cgi-bin
    url: /cgi-bin/
serveradmin: webmaster@paladin-extensions.com
serveralias: www.paladin-extensions.com mail.paladin-extensions.com
servername: paladin-extensions.com
ssl: 1
usecanonicalname: 'Off'
user: palavpvb
userdirprotect: ''
