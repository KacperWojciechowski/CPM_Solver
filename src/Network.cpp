#include "Network.h"

/**
 * Output stream operator for the Path.
 */
auto OpRes::operator<<(std::ostream& stream, const OpRes::Path& p) -> std::ostream&
{
	stream << "Length: " << p.length << " units\n";

	for (std::size_t i = 0; auto & vertex : p.path)
	{
		stream << vertex;;
		if (i < p.path.size() - 1)
		{
			stream << " -> ";
		}
		i++;
	}
	stream << '\n';
	stream << std::flush;

	return stream;
}




OpRes::Path::Path(std::vector<std::size_t> path, int32_t length)
	: path(path),
	length(length)
{
}




/**
 * Constructor creating a topologically sorted graph based on the cost matrix.
 * 
 * \param input The input stream to read the cost matrix from.
 * \param node_count Amount of nodes in the cost matrix.
 */
OpRes::Network::Network(std::istream& input, std::size_t node_count)
	: node_count(node_count),
	cost_matrix(node_count),
	arrival_times(node_count),
	departure_times(node_count),
	net(0)
{
	this->load_cost_matrix(input);
	this->prepare_net();
}
