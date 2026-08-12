#include <boost/asio/io_context.h>
#include <boost/asio/ip/address.h>

boost::asio::awaitable<void> handleSession(boost::asio::ip::tcp::socket socket){
    
};

boost::asio::awaitable<void> listen(boost::asio::ip::tcp::endpoint endpoint){
    auto executor = co_await boost::asio::this_coro::executor;
    boost::asio::ip::tcp::acceptor acceptor(execute, endpoint);

    while(true){
        boost::asio::ip::tcp::socket socket = acceptor.async_accept(boost::asio::use_awaitable);
        boost::asio::co_spawn(executor, std::move(socket), boost::asio::detach);
    }
}

int main(){
    try{
        const auto address = boost::asio::ip::make_address("0.0.0.0");
        const unsigned short port = 8080;
        const int thread = 4;
        boost::asio::io_context ioc{thread};

        boost::asio::signal_set signal(ioc, SIGINT, SIGTERM);
        signal.async_wait([&ioc](boost::asio::system::error_code&, int){
            ioc.stop();
        })

        boost::asio::co_spawn(ioc, listen(boost::asio::ip::tcp::endpoint{address, port}), boost::asio::detach);
        std::vector<std::thread> pool;
        pool.reserve(thread - 1);
        for (int i = 0; i < thread - 1; i++){
            pool.emplace_back([&ioc]{ioc.run()});
        }
        ioc.run();

        for (auto& th : pool){
            if (th.joinable()){
                th.join();
            }
        }

    }catch(const std::exception& e){
        std::cerr << "Fatal error " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return 0;
}
