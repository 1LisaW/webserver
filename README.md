# Webserver

This project is a simple C-based web server implementation that supports handling HTTP requests and serving static files. It includes features such as file uploads, directory listing, and custom error pages.

## Features

- **HTTP Request Handling**: The server can handle GET, POST, and DELETE requests.
- **Server Config file**: Server configuration file syntax was inspired by basic nginx config notation.
- **Static File Serving**: Serve static files from the `www` directory.
- **File Uploads**: Supports file uploads via multipart/form-data.
- **Custom Error Pages**: Custom 404 error page.
- **Directory Listing**: List files in a directory.

## Setup

1. **Clone the repository**:
    ```sh
    git clone <repository-url>
    cd webserver
    ```

2. **Build the project**:
    ```sh
    make
    ```

3. **Run the server**:
    ```sh
    ./webserver ./config
    ```

## Usage

- Place your static files in the [www] directory.
- Change server configuration file according to your preferences.
- Access the server via `http://localhost:<port>`.

## File Uploads

- Upload files using the forms available in `www/upload/index copy.html`. File management only available with a help of php-cgi.

## Custom Error Pages

- Custom 404 error page is located in [404.html].

## License

This project is licensed under the MIT License.

