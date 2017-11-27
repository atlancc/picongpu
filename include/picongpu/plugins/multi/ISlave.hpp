/* Copyright 2017 Rene Widera
 *
 * This file is part of PIConGPU.
 *
 * PIConGPU is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PIConGPU is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PIConGPU.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "picongpu/simulation_defines.hpp"
#include "picongpu/plugins/multi/IHelp.hpp"

#include <pmacc/pluginSystem/INotify.hpp>

#include <memory>


namespace picongpu
{
namespace plugins
{
namespace multi
{

    /** Interface for a slave plugin
     *
     * A plugin which fulfil l this interface can be used as slave plugin for
     * multi::Master.
     *
     * A slave must register itself to the PluginConnector to receive the notify calls.
     */
    struct ISlave : public pmacc::INotify
    {
        /** creates a instance of ISlave
         *
         * @tparam T_Slave type of the interface implementation (must inherit from ISlave)
         * @param help plugin defined help
         * @param id index of the plugin, range: [0;help->getNumPlugins())
         */
        template<
            typename T_Slave
        >
        static std::shared_ptr< ISlave > create(
            std::shared_ptr< IHelp > & help,
            size_t const id,
            MappingDesc* cellDescription
        )
        {
            return std::shared_ptr< ISlave >(
                new T_Slave(
                    help,
                    id,
                    cellDescription
                )
            );
        }

        //! must be implemented by the user
        static std::shared_ptr< IHelp > getHelp();

        //! restart the plugin from a checkpoint
        virtual void restart(
            uint32_t restartStep,
            std::string const & restartDirectory
        ) = 0;

        //! create a check point forthe plugin
        virtual void checkpoint(
            uint32_t currentStep,
            std::string const & checkpointDirectory
        ) = 0;
    };

} // namespace multi
} // namespace plugins
} // namespace picongpu