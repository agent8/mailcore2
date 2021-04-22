@mkdir ..\..\telsa\build-win\include\MailCore
@for /F "delims=" %%a in (build_headers.list) do @copy "..\%%a" ..\..\telsa\build-win\include\MailCore
@echo "done" >_headers_depends
