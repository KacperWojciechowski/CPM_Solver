#include "Network.h"

/**
 * Output stream operator for the Path.
 */
auto OpRes::operator<<(std::ostream& stream, const OpRes::Path& p) -> std::ostream&
{
	/*
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

	return stream;*/ 
}




OpRes::Path::Path(std::vector<std::size_t> path, int32_t length)
	: path(path),
	length(length)
{
}
