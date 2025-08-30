# mod_aspdotnet
This repository has re-opened from mod_aspdotnet to provide support for Apache2.4 and other future releases on multple platform architectures.

[![GitHub issues](https://img.shields.io/github/issues/SagnikGanguly96/mod_aspdotnet)](https://github.com/SagnikGanguly96/mod_aspdotnet/issues)
[![GitHub forks](https://img.shields.io/github/forks/SagnikGanguly96/mod_aspdotnet)](https://github.com/SagnikGanguly96/mod_aspdotnet/network)
[![GitHub stars](https://img.shields.io/github/stars/SagnikGanguly96/mod_aspdotnet)](https://github.com/SagnikGanguly96/mod_aspdotnet/stargazers)
[![GitHub license](https://img.shields.io/github/license/SagnikGanguly96/mod_aspdotnet)](https://github.com/SagnikGanguly96/mod_aspdotnet/blob/master/LICENSE)


What is mod_aspdotnet?
================================
**mod_aspdotnet** is an Apache module hosted which is now came to an end of support. It was first hosted by Apache HTTPD after they have retired **mod_aspdotnet** it has been migrated to http://sourceforge.net/projects/mod-aspdotnet, they have also suspended development of the project on that time the project was for Apache 2.2 (x86/32bts) only, but then the project again migrated to https://github.com/stjeong/mod_aspdotnet by [SeongTae Jeong](https://github.com/stjeong) and he had provided support for Apache 2.4 (x86/32bits). Now the project has been pulled from https://github.com/stjeong/mod_aspdotnet and upgraded for multiple architectures 32bits/64bits and re-opened by [Sagnik Ganguly](https://github.com/SagnikGanguly96) at https://github.com/SagnikGanguly96/mod_aspdotnet. Now the next plan is to provide continuous support for the project in the coming future releases of Apache HTTPD.

You have to install appropriate modules for your environment as follows.

| Apache Version | mod_aspdotet																										|		Architecture		| .NET  |
|----------------|------------------------------------------------------------------------------------------------------------------|---------------------------|-------|
| 2.0            | [mod_aspdotnet-2.0.0.msi](https://archive.apache.org/dist/httpd/mod_aspdotnet/mod_aspdotnet-2.0.0.msi)			|		32bits (x86)		| CLR 2 |
| 2.2            | [mod_aspdotnet-2.2.0.2006-setup-r2.msi](http://sourceforge.net/project/platformdownload.php?group_id=175077)		|		32bits (x86)		| CLR 2 |
| 2.4            | [mod_aspdotnet-2.2.0-2017](https://github.com/stjeong/mod_aspdotnet)												|		32bits (x86)		| CLR 4 |
| 2.4            | [mod_aspdotnet-2.4-2019](https://github.com/SagnikGanguly96/mod_aspdotnet/releases)								|	32/64 bits (x86/x64)	| CLR 4 |

How to Build
================================
## *Using Visual Studio IDE*
Run Visual Studio

Open the mod_aspdotnet.sln

Select the build flavors (Solution Configuration & Platform)

Click on the Build button located at the top toolbar or right-click on the "mod_aspdotnet" project and select the "Build" option from the context menu (If in any case the building of the solution gets failed due to "Apache.Web.tlb", just build the `Apache.Web` project first and then build the solution)

After the build finishes, 3 files (1. Apache.Web.dll, 2. mod_aspdotnet.so, 3. resolve_apache.dll) will be created under the following directories:

For "Debug 2.4" build, the files are located under "win32"(for Win32 platform build) or "x64"(for x64 platform build) under "Debug24" folder will be created on the solution directory
For "Release 2.4" build, the files are located under "win32"(for Win32 platform build) or "x64"(for x64 platform build) under "Release24" folder will be created on the solution directory

## *Using Visual Studio CLI*
The top level workspace mod_aspdotnet.sln is invoked for a release build invoke with the syntax:
  `set APACHE24_PATH=d:\path\to\apache2.4`
  `devenv mod_aspdotnet.sln /useenv /build "Release 2.4" /project mod_aspdotnet`

The necessary files, mod_aspdotnet.so [+.pdb for debug symbols] and the
Apache.Web.dll [+.pdb] are built into the installer.msi package at 
the top-level Release/ directory of this module.

It is absolutely critical that this build occurs using the Visual Studio
.NET 2005 (al la 8.0) version.  Older VS 7.x and earlier compilers won't 
support the C++ CLR syntax used for this module, and newer VS compilers 
may again change the CLR C++ syntax to be entirely incompatible with the
sources.

The Apache.Web.dll is no longer temporarily registered, it's type library
(.tlb file) is extracted using tlbexp.  Earlier notes about this should be
ignored.

We build Apache.Web.dll with delay-load of libhttpd, libapr and libaprutil 
dll's.  This is important since Apache.Web.dll normally can't be loaded,
even for the .NET framework tools to inspect the .dll, unless it is literally 
adjacent (in the same directory) to Apache's .dll's.  And Apache.Web.dll must
be in the Global Assembly Cache to participate in the `System.Web` framework.
So, using this alternate delay-load method, Apache.Web.dll can be loaded 
(provided we don't instantiate an Apache.Web.WorkerRequest object), even when
it cannot resolve the path to Apache's dll's in the Serverroot/bin directory.

Before using InstallShield to actually package a release build, the syntax;
`devenv mod_aspdotnet.sln /useenv /build "Release 2.4" /project resolve_apache`

will build the helper .dll to allow the installer to search the local machine
for installations of Apache.exe (Release flavor) or httpd.exe (Release 2.2).

How to Install
================================
## *For IDE Builds*
After building mod_aspdotnet successfully, you will have 3 files which are:
	1.) Apache.Web.dll
	2.) mod_aspdotnet.so
	3.) resolve_apache.dll
All you need to do is just add the "Apache.Web.dll" to the Global Assembly Cache (GAC). To do this, follow the steps below:

**First,** Open Visual Studio Command Prompt or a Command Prompt with Eleveted Permissions
	
**Second,** Run the following command:
	`gacutil.exe /i "driveLetter:\\path\to\mod_aspdotnet24_solution_folder\Release24\platform\Apache.Web.dll"`
For example, we have a x64 build and the files are located at "D:\Projects\mod_aspdotnet24\Release24\x64\", then we need to execute the following command:
    `gacutil /i "D:\Projects\mod_aspdotnet24\Release24\x64\Apache.Web.dll"`

**Third,** After the "Apache.Web.dll" is added to the GAC, copy the "mod_aspdotnet.so" from the release directory t the "Apache2.4_Installation_directry\modules" directory

**Fourth,** After all the steps has been completed successfully, open Apache HTTPD 2.4 Configuration file "Apache2.4_Installation_directry\conf\httpd.conf" and add the following code at the end of the file:
```
		##### ASP.NET CONFIGURATION #####
		AddHandler asp.net asax ascx ashx asmx aspx axd config cs csproj licx rem resources resx soap vb vbproj vsdisco webinfo
		<IfModule mod_aspdotnet.cpp>
			# Mount the ASP.NET /asp application
			AspNetMount /apacheAsp "D:/httpd/apacheAsp" #Change "/apacheAsp" to your desired ASP.NET application name and the directory to the location of your desired mount point (in that location you will add your ASP.NET files)
			#/SampleASP is the alias name for asp.net to execute
			#"c:/SampleASP" is the actual execution of files/folders in that location

			# Map all requests for /asp to the application files
			Alias /apacheAsp "D:/httpd/apacheAsp" #Change "/apacheAsp" to your desired alias of the ASP.NET applications and the directory to the location of your ASP.NET mount point (the location must be same as "AspNetMount" directive location)
			#maps /SampleASP request to "c:/SampleASP"
			#now to get to the /SampleASP type http://localhost/SampleASP
			#It'll redirect http://localhost/SampleASP to "c:/SampleASP"

			# Allow asp.net scripts to be executed in the /SampleASP example
			<Directory "E:/httpd/apacheAsp"> #Change the directory to the location of your ASP.NET mount point (the location must be same as "AspNetMount" directive location)
				Options FollowSymlinks ExecCGI
				Order allow,deny
				Allow from all
				DirectoryIndex index.htm index.aspx
				#default the index page to .htm and .aspx
			</Directory>

			# For all virtual ASP.NET webs, we need the aspnet_client files
			# to serve the client-side helper scripts.
			AliasMatch /aspnet_client/system_web/(\d+)_(\d+)_(\d+)_(\d+)/(.*) "C:/Windows/Microsoft.NET/Framework/v$1.$2.$3/ASP.NETClientFiles/$4"
			<Directory "C:/Windows/Microsoft.NET/Framework/v*/ASP.NETClientFiles">
				Options FollowSymlinks
				Order allow,deny
				Allow from all
			</Directory>
		</IfModule>
```
**Fifth,** Now save the "httpd.conf" file and create the directory specified in the "AspNetMount" directive and restart apache httpd 2.4 server

**Sixth,** After restarting the server, create a aspx file called "info.aspx" inside the folder specified in the "AspNetMount" directive and paste the following code inside the file,
    `<%@ Page Trace="true" Language="C#" ContentType="text/html" ResponseEncoding="utf-8" %>`

**Seventh,** Now save the file and vsit the link "localhost/apacheAsp/info.aspx" or "localhost:port/apacheAsp/info.aspx" and you wll able to see a page printing all the server informations.
But remember to change the port with the port you have configured (most commonly 8080) and "apacheAsp" with alias you have set by "AspNetMount" and "Alias" directive.

**Eighth,** If you can't see a page or an error by `ASP.NET` (i.e, the file starts downloadng or throwing 500 Error) please check your configuration.



## *For CLI Builds*
YOU should test that the module runs under both the full .NET Framework SDK, 
as well as within the .NET Framework Runtime environment only.  A number 
of internal behaviors vary between these two environments, and Exceptions,
destruction, construction and failure cases will manifest differently between
the two environments.

`ASP.NET` requires the Apache::Web::Request object to be registered in 
the Global Assembly Cache in order to instantiate it's host container.
So it is not possible to install Apache.Web.dll in the 'usual' modules
subdirectory of Apache HTTP Server.

In order to install a reference into the Global Assembly Cache (for testing
the release build or debug build) use;
  `regasm d:\path-to-apache\bin\Apache.Web.dll`
  `gacutil /ir Apache.Web.dll FILEPATH d:\path-to-apache\bin\Apache.Web.dll Apache.Web`

This installs Apache.Web.dll by reference to the built assembly.  Note that
UAC will prevent you from doing this in Vista or 2008 and you may need to
launch a command shell "run as Administrator" in order to complete this
package registration in the global cache.

This may *NOT* work on an end-user's machine without the .NET Platform SDK.  
Those tools [regasm/gacutil] were not officially going to be distributed
with the retail .NET runtime redistributables.  Instead, the .msi installer, 
has all details for registering the `Apache.Web` assembly into the Global 
Assembly Cache, is entrusted to install `Apache.Web` to the GAC for end-users.
Note that it appears they are installed with the runtime, but all warnings
by Microsoft were to the contrary.

#### *TODO:*
Consider pre-compiling the package into native code prior to distribution.
(Apparently, InstallShield always does this for GAC-registered modules, so
this consideration might be moot.)

Consider building a roll-up assembly integrating the libhttpd et. al. with
the Apache.Web.dll package.  Perhaps we can force them to live in different
locations with this method.  Note roll up assemblies -reference- the other
.dll's [that assembly is a .dll itself] but it does not actually merge the
other .dll's into a single package.

Note that the .msi package searches for apache/bin/apache.exe up to 3 levels 
deep from the local hard drives, in sequence.  It aught to test further, as
necessary, or allow explicitly long paths, if the user chooses.  The path can
be manually specified in the installer, though, so the issue is not fatal,
and the 3 level depth avoids waiting a half hour when invoking the installer.

## *From ZIP/RAR Releases*
**First,** Download the required version of the release and extract to a directory.

**Second,** AFter extracting, you will have 3 files,
    ***1. Apache.Web.dll
      2. mod_aspdotnet.so
      3. resolve_apache.dll***
but you need only first & second file. Note down the location of **Apache.Web.dll** file and open command prompt with eleveted permissions and run the following command (don't forget to change the location):
    `gacutil.exe /i "driveLetter:\\path\to\mod_aspdotnet24_extracted_folder\Apache.Web.dll`
For example, we have a x64 build and the files are located at "D:\Projects\mod_aspdotnet24\Release24\x64\", then we need to execute the following command:
	`gacutil /i "D:\Downloads\mod_aspdotnet24\Apache.Web.dll"`

**Third,** Copy the **mod_aspdotnet.so** to the "modules\" directory under Apache Installation Directory.
    For example, we have nstalled Apache2.4 in "C:\httpd", we need to copy the **mod_aspdotnet.so** to "C:\httpd\modules\" and the location of **mod_aspdotnet.so** will be "C:\httpd\modules\mod_aspdotnet.so".

**Fourth,** After all the steps above has been completed successfully, open Apache HTTPD 2.4 Configuration file "Apache2.4_Installation_directry\conf\httpd.conf" (i.e, "C:\httpd\conf\httpd.conf") and add the following code at the end of the file:
```
        ##### ASP.NET CONFIGURATION #####
		AddHandler asp.net asax ascx ashx asmx aspx axd config cs csproj licx rem resources resx soap vb vbproj vsdisco webinfo
		<IfModule mod_aspdotnet.cpp>
			# Mount the ASP.NET /asp application
			AspNetMount /apacheAsp "D:/httpd/apacheAsp" #Change "/apacheAsp" to your desired ASP.NET application name and the directory to the location of your desired mount point (in that location you will add your ASP.NET files)
			#/SampleASP is the alias name for asp.net to execute
			#"c:/SampleASP" is the actual execution of files/folders in that location

			# Map all requests for /asp to the application files
			Alias /apacheAsp "D:/httpd/apacheAsp" #Change "/apacheAsp" to your desired alias of the ASP.NET applications and the directory to the location of your ASP.NET mount point (the location must be same as "AspNetMount" directive location)
			#maps /SampleASP request to "c:/SampleASP"
			#now to get to the /SampleASP type http://localhost/SampleASP
			#It'll redirect http://localhost/SampleASP to "c:/SampleASP"

			# Allow asp.net scripts to be executed in the /SampleASP example
			<Directory "E:/httpd/apacheAsp"> #Change the directory to the location of your ASP.NET mount point (the location must be same as "AspNetMount" directive location)
				Options FollowSymlinks ExecCGI
				Order allow,deny
				Allow from all
				DirectoryIndex index.htm index.aspx
				#default the index page to .htm and .aspx
			</Directory>

			# For all virtual ASP.NET webs, we need the aspnet_client files
			# to serve the client-side helper scripts.
			AliasMatch /aspnet_client/system_web/(\d+)_(\d+)_(\d+)_(\d+)/(.*) "C:/Windows/Microsoft.NET/Framework/v$1.$2.$3/ASP.NETClientFiles/$4"
			<Directory "C:/Windows/Microsoft.NET/Framework/v*/ASP.NETClientFiles">
				Options FollowSymlinks
				Order allow,deny
				Allow from all
			</Directory>
		</IfModule>
```
**Fifth,** Now save the "httpd.conf" file and create the directory specified in the "AspNetMount" directive and restart apache httpd 2.4 server

**Sixth,** After restarting the server, create an aspx file called "info.aspx" inside the folder specified in the "AspNetMount" directive and paste the following code inside the file,
		`<%@ Page Trace="true" Language="C#" ContentType="text/html" ResponseEncoding="utf-8" %>`

**Seventh,** Now save the file and vsit the link "localhost/apacheAsp/info.aspx" or "localhost:port/apacheAsp/info.aspx" and you wll able to see a page printing all the server informations.
			But remember to change the port with the port you have configured (most commonly 8080) and "apacheAsp" with alias you have set by "AspNetMount" and "Alias" directive.

**Eighth,** If you can't see a page or an error by `ASP.NET` (i.e, the file starts downloadng or throwing 500 Error) please check your configuration.

## *From Installer (MSI/EXE) Releases*
Nothing to explain very much, just download appropriate version of the installer and run the installer and everything will be taken care of by the installer.
**Just one thing to note is you have downloaded appropriate version of the installer and create an Envioronment Variable for `APACHE24_PATH` with the value as the location of the Apache 2.4 or select the location of Apache2.4 installation.**
> Apache.Web.dll and mod_aspdotnet.so have dependencies on [Microsoft Visual C++ Redistributable for Visual Studio 2017](https://www.visualstudio.com/downloads/)

---

Change Log
================================


### *Version 2.4 - May 23, 2019*

---

### Added
* Version 2.4 for Apache HTTPD 2.4 (x86/x64) has been released
* Added support for 32/64bits (x86/x64) platforms

---

Reqeuests or Contributing to Repository
================================
If you need some features or whatever, make an issue at [https://github.com/SagnikGanguly96/mod_aspdotnet24/issues](https://github.com/SagnikGanguly96/mod_aspdotnet24/issues)
**Any help and advices for this repo are welcome.**

License
================================
[Apache License V2.0](https://github.com/SagnikGanguly96/mod_aspdotnet24/blob/master/LICENSE.txt)
(Refer to LICENSE.txt)
