/**
 * @file   shadow_PSTs.hpp
 * @author Toni Oliver <toni@shadowrobot.com>
 * @date   Th Oct 20 10:06:14 2011
 *
* Copyright 2011 Shadow Robot Company Ltd.
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 2 of the License, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*
 * @brief This is a class for accessing the data from the
 *        PSTs tactiles.
 *
 *
 */

#ifndef _SHADOW_PSTS_HPP_
#define _SHADOW_PSTS_HPP_

#include <vector>
#include <sr_robot_msgs/ShadowPST.h>
#include <realtime_tools/realtime_publisher.h>

#include <sr_hardware_interface/tactile_sensors.hpp>
#include "sr_robot_lib/generic_tactiles.hpp"
#include "sr_robot_lib/generic_updater.hpp"

namespace tactiles
{
  template <class StatusType, class CommandType>
  class ShadowPSTs :
    public GenericTactiles<StatusType, CommandType>
  {
  public:
    ShadowPSTs(ros::NodeHandle nh, std::string device_id, std::vector<generic_updater::UpdateConfig> update_configs_vector, operation_mode::device_update_state::DeviceUpdateState update_state);
    ShadowPSTs(ros::NodeHandle nh, std::string device_id, std::vector<generic_updater::UpdateConfig> update_configs_vector, operation_mode::device_update_state::DeviceUpdateState update_state, boost::shared_ptr< std::vector<GenericTactileData> > init_tactiles_vector);

    void init(std::vector<generic_updater::UpdateConfig> update_configs_vector, operation_mode::device_update_state::DeviceUpdateState update_state);

    /**
     * This function is called each time a new etherCAT message
     * is received in the sr06.cpp driver. It  updates the tactile
     * sensors values contained in tactiles_vector.
     *
     * @param status_data the received etherCAT message
     */
    virtual void update(StatusType* status_data);

    /**
     * Publish the information to a ROS topic.
     *
     */
    virtual void publish();

    /**
     * This function adds the diagnostics for the tactiles to the
     * multi diagnostic status published by the hand.
     */
    virtual void add_diagnostics(std::vector<diagnostic_msgs::DiagnosticStatus> &vec,
                                 diagnostic_updater::DiagnosticStatusWrapper &d);

    /// the vector containing the data for the tactiles.
    boost::shared_ptr< std::vector<PST3Data> > tactiles_vector;

    virtual std::vector<AllTactileData>* get_tactile_data();

  protected:

    // Tactile sensor real time publisher
    boost::shared_ptr<realtime_tools::RealtimePublisher<sr_robot_msgs::ShadowPST> > tactile_publisher;
  };//end class
}//end namespace

/* For the emacs weenies in the crowd.
Local Variables:
   c-basic-offset: 2
End:
*/

#endif /* _SHADOW_PSTS_HPP_ */
