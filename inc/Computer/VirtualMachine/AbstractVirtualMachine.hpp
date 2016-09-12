#ifndef ABSTRACTVIRTUALMACHINE_HPP
#define ABSTRACTVIRTUALMACHINE_HPP

class AbstractVirtualMachine
{
public:
	AbstractVirtualMachine(){};
	virtual ~AbstractVirtualMachine(){};

	/**
	 * Loads a program into memory
	 * @param[in] base starting address of program loaded
	 * @param[out] end ending address of program loaded
	 * @param[in] program program to load
	 * @return error code
	 */
	virtual int Load(unsigned int base, unsigned int &offset, std::vector<unsigned int> program) = 0;

	/**
	 * Run the program until a blocking operation 
	 * or error occurs
	 * such as an input request
	 */
	virtual int Run() = 0;

private:
};

#endif //ABSTRACTVIRTUALMACHINE_HPP
