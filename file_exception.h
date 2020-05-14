#ifndef FILE_EXCEPTION_H
#define FILE_EXCEPTION_H

class FileNotFoundException : public std::exception {
public:
	const char *what() const throw() {
		return "File not found";
	}
};

#endif // FILE_EXCEPTION_H
