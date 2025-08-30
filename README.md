# mod_aspdotnet
This repository has been reopened from mod_aspdotnet to provide support for Apache 2.4 and future releases across multiple platform architectures.

[![GitHub issues](https://img.shields.io/github/issues/SagnikGanguly96/mod_aspdotnet)](https://github.com/SagnikGanguly96/mod_aspdotnet/issues)
[![GitHub forks](https://img.shields.io/github/forks/SagnikGanguly96/mod_aspdotnet)](https://github.com/SagnikGanguly96/mod_aspdotnet/network)
[![GitHub stars](https://img.shields.io/github/stars/SagnikGanguly96/mod_aspdotnet)](https://github.com/SagnikGanguly96/mod_aspdotnet/stargazers)
[![GitHub license](https://img.shields.io/github/license/SagnikGanguly96/mod_aspdotnet)](https://github.com/SagnikGanguly96/mod_aspdotnet/blob/master/LICENSE)


What is mod_aspdotnet?
================================
**mod_aspdotnet** is an Apache module that has reached the end of its official support. Originally hosted by Apache HTTPD, it was retired and migrated to [SourceForge](http://sourceforge.net/projects/mod-aspdotnet) with development paused. That release supported Apache 2.2 (x86/32-bit) only. Later, the project was migrated again to [GitHub](https://github.com/stjeong/mod_aspdotnet) by [SeongTae Jeong](https://github.com/stjeong), providing support for Apache 2.4 (x86/32-bit).  

The project has now been pulled from SeongTae Jeong’s repository, upgraded for multiple architectures (32-bit/64-bit), and reopened by [Sagnik Ganguly](https://github.com/SagnikGanguly96) at [GitHub](https://github.com/SagnikGanguly96/mod_aspdotnet). The ongoing plan is to provide continuous support for future releases of Apache HTTPD.

You must install the appropriate module for your environment as follows:

| Apache Version | mod_aspdotnet                                                                                                     | Architecture       | .NET  |
|----------------|------------------------------------------------------------------------------------------------------------------|-------------------|-------|
| 2.0            | [mod_aspdotnet-2.0.0.msi](https://archive.apache.org/dist/httpd/mod_aspdotnet/mod_aspdotnet-2.0.0.msi)           | 32-bit (x86)      | CLR 2 |
| 2.2            | [mod_aspdotnet-2.2.0.2006-setup-r2.msi](http://sourceforge.net/project/platformdownload.php?group_id=175077)    | 32-bit (x86)      | CLR 2 |
| 2.4            | [mod_aspdotnet-2.2.0-2017](https://github.com/stjeong/mod_aspdotnet)                                             | 32-bit (x86)      | CLR 4 |
| 2.4            | [mod_aspdotnet-2.4-2019](https://github.com/SagnikGanguly96/mod_aspdotnet/releases)                               | 32/64-bit (x86/x64)| CLR 4 |

How to Build
================================
## *Using Visual Studio IDE*
1. Open Visual Studio.
2. Open the `mod_aspdotnet.sln` solution file.
3. Select the build configuration and platform (Solution Configuration & Platform).
4. Click the **Build** button on the toolbar, or right-click the `mod_aspdotnet` project and select **Build**.  
   *(If the build fails due to `Apache.Web.tlb`, build the `Apache.Web` project first, then rebuild the solution.)*
5. After building, three files will be created:

   - `Apache.Web.dll`
   - `mod_aspdotnet.so`
   - `resolve_apache.dll`

   **Locations:**
   - Debug 2.4: `win32/Debug24` (Win32) or `x64/Debug24` (x64)
   - Release 2.4: `win32/Release24` (Win32) or `x64/Release24` (x64)

## *Using Visual Studio CLI*
For a release build, use the syntax:

```cmd
set APACHE24_PATH=d:\path\to\apache2.4
devenv mod_aspdotnet.sln /useenv /build "Release 2.4" /project mod_aspdotnet
```

This builds `mod_aspdotnet.so` and `Apache.Web.dll` (with optional debug symbols) into the `Release/` directory.

**Important:**

* Use Visual Studio .NET 2005 (v8.0). Older compilers (VS 7.x or earlier) won't support the C++/CLI syntax. Newer compilers may be incompatible.
* `Apache.Web.dll` uses delay-load for `libhttpd`, `libapr`, and `libaprutil`. It must reside in the GAC to integrate with `System.Web`.

Before using InstallShield:
```cmd
devenv mod_aspdotnet.sln /useenv /build "Release 2.4" /project resolve_apache
```

This builds the helper `.dll` allowing the installer to detect Apache installations.

# How to Install

## *For IDE Builds*

1. After building, add `Apache.Web.dll` to the Global Assembly Cache (GAC):
```cmd
gacutil.exe /i "driveLetter:\\path\to\mod_aspdotnet24_solution_folder\Release24\platform\Apache.Web.dll"
```

Example for x64 build:
```cmd
gacutil /i "D:\Projects\mod_aspdotnet24\Release24\x64\Apache.Web.dll"
```

2. Copy `mod_aspdotnet.so` to the `modules` directory in the Apache 2.4 installation folder.
3. Edit `httpd.conf` and append:
```apache
##### ASP.NET CONFIGURATION #####
AddHandler asp.net asax ascx ashx asmx aspx axd config cs csproj licx rem resources resx soap vb vbproj vsdisco webinfo
<IfModule mod_aspdotnet.cpp>
    AspNetMount /apacheAsp "D:/httpd/apacheAsp"
    Alias /apacheAsp "D:/httpd/apacheAsp"
    <Directory "E:/httpd/apacheAsp">
        Options FollowSymlinks ExecCGI
        Order allow,deny
        Allow from all
        DirectoryIndex index.htm index.aspx
    </Directory>
    AliasMatch /aspnet_client/system_web/(\d+)_(\d+)_(\d+)_(\d+)/(.*) "C:/Windows/Microsoft.NET/Framework/v$1.$2.$3/ASP.NETClientFiles/$4"
    <Directory "C:/Windows/Microsoft.NET/Framework/v*/ASP.NETClientFiles">
        Options FollowSymlinks
        Order allow,deny
        Allow from all
    </Directory>
</IfModule>
```

4. Save `httpd.conf`, create the `AspNetMount` directory, and restart Apache.
5. Create `info.aspx` inside the mount directory:
```aspx
<%@ Page Trace="true" Language="C#" ContentType="text/html" ResponseEncoding="utf-8" %>
```

6. Visit `http://localhost/apacheAsp/info.aspx` (or adjust port and alias as needed) to confirm installation.
7. If errors occur (e.g., file downloads or 500 errors), check configuration.

## *For CLI Builds*

* Test under both .NET Framework SDK and runtime environments. Behavior may vary.
* Register `Apache.Web.dll` in the GAC:
```cmd
regasm d:\path-to-apache\bin\Apache.Web.dll
gacutil /ir Apache.Web.dll FILEPATH d:\path-to-apache\bin\Apache.Web.dll Apache.Web
```

* Installer `.msi` handles GAC registration for end users without requiring the SDK.

## *From ZIP/RAR Releases*

1. Extract release files.
2. Register `Apache.Web.dll` in the GAC: ```gacutil /i "D:\Downloads\mod_aspdotnet24\Apache.Web.dll"```

3. Copy `mod_aspdotnet.so` to `modules\` under Apache installation.
4. Configure `httpd.conf` as described in IDE builds.
5. Restart Apache and verify with `info.aspx`.

## *From Installer (MSI/EXE) Releases*

* Download and run the installer.
* Ensure `APACHE24_PATH` is set to the Apache 2.4 installation directory or select the path to the Apache installation directory.
* Dependencies: [Microsoft Visual C++ Redistributable for Visual Studio 2022](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170).

---

# Change Log

### *Version 2.4 - May 23, 2019*

**Added**

* Apache HTTPD 2.4 support (x86/x64)
* 32/64-bit platform compatibility

---

# Requests or Contributing

Create an issue at [GitHub Issues](https://github.com/SagnikGanguly96/mod_aspdotnet24/issues) for feature requests or contributions.
**All help and advice are welcome.**

# License

[Apache License V2.0](https://github.com/SagnikGanguly96/mod_aspdotnet24/blob/master/LICENSE.txt)

