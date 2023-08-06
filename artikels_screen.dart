import 'package:flutter/material.dart';
import 'package:mobile_ta_padi_fix/used/model/Article.dart';

class ArtikelsScreen extends StatelessWidget {
  ArtikelsScreen({super.key});

  // Dummy data artikel (ganti dengan data sesuai kebutuhan)
  final List<Article> articles = [
    Article(
      imagePath: 'assets/img1.jpeg',
      title: 'Padi: Sumber Makanan Utama di Asia',
      description:
          'Pelajari bagaimana padi telah menjadi sumber makanan utama bagi masyarakat Asia selama berabad-abad dan peran pentingnya dalam ketahanan pangan.',
    ),
    Article(
      imagePath: 'assets/img2.jpeg',
      title: 'Teknologi Pertanian Terkini untuk Meningkatkan Hasil Padi',
      description:
          'Temukan teknologi terbaru yang digunakan dalam pertanian untuk meningkatkan hasil padi, termasuk penggunaan drone dan sensor untuk pengawasan lahan.',
    ),
    Article(
      imagePath: 'assets/img3.jpeg',
      title: 'Ragam Varietas Padi di Indonesia dan Manfaatnya',
      description:
          'Pelajari tentang beragam varietas padi yang ada di Indonesia, termasuk beras organik, hitam, dan merah, serta manfaat kesehatan yang dimilikinya',
    ),
    Article(
      imagePath: 'assets/img4.jpeg',
      title: 'Peran Padi dalam Perubahan Iklim dan Adaptasi Pertanian',
      description:
          'Eksplorasi bagaimana perubahan iklim mempengaruhi pertanian padi dan upaya adaptasi yang dapat dilakukan untuk menghadapinya.',
    ),
    Article(
      imagePath: 'assets/img5.jpeg',
      title: 'Pemanfaatan Limbah Pertanian Padi untuk Energi dan Bahan Baku',
      description:
          'Tinjau potensi pemanfaatan limbah pertanian padi sebagai sumber energi terbarukan dan bahan baku dalam industri.',
    ),
    Article(
      imagePath: 'assets/img6.jpeg',
      title:
          'Revitalisasi Pertanian Padi Tradisional: Menjaga Kearifan Lokal dan Keberlanjutan Lingkungan',
      description:
          'Eksplorasi bagaimana revitalisasi pertanian padi tradisional dapat menjaga kearifan lokal dan mengedepankan prinsip keberlanjutan lingkungan.',
    ),
    // Tambahkan artikel lainnya sesuai kebutuhan
  ];

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        appBar: AppBar(
          title: Text(
            "Artikel",
            style: TextStyle(color: Colors.black),
          ),
          backgroundColor: Colors.amber,
          iconTheme: IconThemeData(
              color: Colors.black), // Set the icon (back button) color to black
        ),
        body: ListView.builder(
          itemCount: articles.length,
          itemBuilder: (context, index) {
            return GestureDetector(
              onTap: () {
                // Navigasi ke halaman detail artikel ketika salah satu artikel diklik
                Navigator.push(
                  context,
                  MaterialPageRoute(
                    builder: (context) =>
                        DetailArtikelScreen(article: articles[index]),
                  ),
                );
              },
              child: Padding(
                padding: const EdgeInsets.all(8.0),
                child: Card(
                  color: Colors.amber,
                  child: Column(
                    children: [
                      SizedBox(height: 10),
                      Image.asset(
                        articles[index].imagePath,
                        width: 200,
                      ),
                      SizedBox(
                        height: 10,
                      ),
                      ListTile(
                        title: Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: Text(
                            articles[index].title,
                            textAlign: TextAlign.center,
                            style: TextStyle(
                                fontSize: 16,
                                color: Colors.black,
                                fontWeight: FontWeight.bold),
                          ),
                        ),
                        subtitle: Text(articles[index].description,
                            textAlign: TextAlign.justify,
                            style: TextStyle(color: Colors.black)),
                      ),
                      SizedBox(height: 10),
                    ],
                  ),
                ),
              ),
            );
          },
        ),
      ),
    );
  }
}

// Halaman detail artikel
class DetailArtikelScreen extends StatelessWidget {
  final Article article;

  DetailArtikelScreen({required this.article});

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        appBar: AppBar(
          title: Text(
            "Detail Artikel",
            style: TextStyle(color: Colors.black),
          ),
          backgroundColor: Colors.amber,
          iconTheme: IconThemeData(
              color: Colors.black), // Set the icon (back button) color to black
        ),
        body: Column(
          children: [
            SizedBox(
              height: 10,
            ),
            Padding(
              padding: const EdgeInsets.all(16.0),
              child: Text(
                article.title,
                textAlign: TextAlign.center,
                style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
              ),
            ),
            SizedBox(
              height: 10,
            ),
            Image.asset(article.imagePath),
            SizedBox(
              height: 10,
            ),
            Padding(
              padding: EdgeInsets.all(16.0),
              child: Text(
                article.description,
                textAlign: TextAlign.justify,
              ),
            ),
          ],
        ),
      ),
    );
  }
}
