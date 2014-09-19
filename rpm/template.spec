Name:           ros-hydro-sr-edc-launch
Version:        1.3.4
Release:        0%{?dist}
Summary:        ROS sr_edc_launch package

Group:          Development/Libraries
License:        GPL
URL:            http://ros.org/wiki/sr_edc_launch
Source0:        %{name}-%{version}.tar.gz

Requires:       ros-hydro-convex-decomposition
Requires:       ros-hydro-diagnostic-aggregator
Requires:       ros-hydro-diagnostic-msgs
Requires:       ros-hydro-diagnostic-updater
Requires:       ros-hydro-ivcon
Requires:       ros-hydro-pr2-bringup
Requires:       ros-hydro-pr2-ethercat
Requires:       ros-hydro-robot-mechanism-controllers
Requires:       ros-hydro-roscpp
Requires:       ros-hydro-self-test
Requires:       ros-hydro-sr-description
Requires:       ros-hydro-sr-ethercat-hand-config
Requires:       ros-hydro-urdf
Requires:       ros-hydro-xacro
BuildRequires:  ros-hydro-catkin

%description
Package with launch files to start the needed nodes for the Shadow Robot
EtherCAT hand.

%prep
%setup -q

%build
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree that was dropped by catkin, and source it.  It will
# set things like CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/hydro/setup.sh" ]; then . "/opt/ros/hydro/setup.sh"; fi
mkdir -p build && cd build
%cmake .. \
        -UINCLUDE_INSTALL_DIR \
        -ULIB_INSTALL_DIR \
        -USYSCONF_INSTALL_DIR \
        -USHARE_INSTALL_PREFIX \
        -ULIB_SUFFIX \
        -DCMAKE_INSTALL_PREFIX="/opt/ros/hydro" \
        -DCMAKE_PREFIX_PATH="/opt/ros/hydro" \
        -DSETUPTOOLS_DEB_LAYOUT=OFF \
        -DCATKIN_BUILD_BINARY_PACKAGE="1" \

make %{?_smp_mflags}

%install
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree that was dropped by catkin, and source it.  It will
# set things like CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/hydro/setup.sh" ]; then . "/opt/ros/hydro/setup.sh"; fi
cd build
make %{?_smp_mflags} install DESTDIR=%{buildroot}

%files
/opt/ros/hydro

%changelog
* Fri Sep 19 2014 Shadow Robot's software team <software@shadowrobot.com> - 1.3.4-0
- Autogenerated by Bloom

