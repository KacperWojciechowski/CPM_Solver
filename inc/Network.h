#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

namespace OpRes
{
	/**
	 * \brief Structure storing information regarding found critical path by the CPM algorithm.
	 */
	struct Path
	{
	public:
		Path() = default;
		Path(std::vector<std::size_t> path, int32_t length);

		/* Stream output operator */
		friend auto operator << (std::ostream& stream, const Path& p) -> std::ostream&;

		std::vector<std::size_t> path;  /**< Vector containing the path in order. */
		int32_t length;					/**< Time needed to traverse the path */
	};




	/**
	 * Class representing the network containing the tasks information.
	 */
	class Network
	{
	public:
		Network(std::istream& input, std::size_t node_count);

		/* Basic interface */
		auto print_cost_matrix() -> void;
		auto print_net_struct() -> void;

		/* Algorithmic interface */
		auto CPM_methode() ->std::vector<Path>;

	private:
		std::size_t node_count;							/**< Amount of tasks within the network */
		std::vector<std::vector<int32_t>> cost_matrix;  /**< Cost matrix of the tasks */
		std::vector<int32_t> arrival_times;				/**< Arrival times for each vertex within the network */
		std::vector<int32_t> departure_times;			/**< Departure times for each vertex within the network */
	
		std::vector<std::vector<uint32_t>> net;			/**< The network topologically sorted structure */

		/* Internal search function for the CPM method */
		auto critical_DFS(std::vector<Path>& paths, std::vector<std::size_t>& path, std::size_t vertex) -> void;
	};
}
