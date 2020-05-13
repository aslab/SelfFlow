
class requisite
{
private:
    bool req_=0;

public:
    bool req()
    {
        if(!req_)
        {
		exe_req();
                return 0;
        }
        else   {return 1;}
    }
    virtual void exe_req(){}

    void complete(){req_=1;}
};
