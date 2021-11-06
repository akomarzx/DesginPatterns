#include<iostream>
#include<vector>
#include<thread>
#include<chrono>
#include<Windows.h>

class IMediaType
{

};

class Music : public IMediaType
{
public:
	std::string Title;
	std::string Artist;
	unsigned short TrackLengthInSeconds;
};

class Video : public IMediaType
{

};



class MusicLibrary
{
private:
	std::vector<IMediaType> MusicCollection;
public:
	void AddMusic(IMediaType&& music)
	{
		MusicCollection.emplace_back(music);
	}
	inline const std::vector<IMediaType>& GetLibrary()const { return MusicCollection; }
};

class MediaPlayer
{
private: 
	MusicLibrary library;
public:
	MediaPlayer(const MusicLibrary& music_library)
		:library{ music_library} {}
	void Play()const;
};

void MediaPlayer::Play() const
{
	for (const auto& music : library.GetLibrary())
	{
		std::cout << "Now Playing : " << music.Title << " By: " << music.Artist << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(music.TrackLengthInSeconds));
		system("CLS");
	}
}


int main()
{
	MusicLibrary library;
	library.AddMusic({ "Fine" , "Taeyeon" , 20 });
	library.AddMusic({ "Blue" , "IU" , 20 });
	library.AddMusic({ "Lion Heart" , "GG" , 30 });

	MediaPlayer Player(library);

	Player.Play();

	return 0;
}